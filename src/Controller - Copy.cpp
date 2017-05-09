#include "flickstr/Controller.h"
#include "flickstr/SearchQueryFactory.h"
#include "flickstr/SearchQueryUrlBuilder.h"
#include "flickstr/HttpRequestFactory.h"
#include "flickstr/XmlParser.h"
#include "flickstr/UrlTransform.h"
#include "flickstr/PhotoDownloadManager.h"
#include "flickstr/PhotoDataHandlerPublic.h"

#include <QDebug>

Controller::Controller(QObject *parent)
    : QObject(parent)
{
    qmlRegisterSingletonType<Controller>("ControllerLib",
                                         1,
                                         0,
                                         "Controller",
                                         &Controller::provider);

    qmlRegisterType<TagModel>("TagModelLib", 1, 0, "TagModel");

    Q_ASSERT(mTagHash.isEmpty());
}

QObject* Controller::provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    static Controller mInstance;

    QQmlEngine::setObjectOwnership(&mInstance, QQmlEngine::CppOwnership);

    return &mInstance;
}

// Entry Point
void Controller::setTag(QString searchTag)
{
    if(searchTag.isNull() || searchTag.isEmpty())
        return;

    if(tagExist(searchTag)) {
        // TODO: TELL QML tag already exist
        // eg. dialog box?
        return;
    }

    execRequest(searchTag);
}

// Avoid duplicate tag search
bool Controller::tagExist(const QString& searchTag) const
{
    bool bExist = false;

    QHash<QString, Tag>::const_iterator it = mTagHash.find(searchTag);
    if(it != mTagHash.end())
        bExist = true;

    return bExist;
}

void Controller::execRequest(const QString &searchTag)
{
    // 1.
    auto searchQuery = buildQuery(searchTag);
    if(!query.isValid())
        return;

    // 2.
    auto url = buildUrl(searchQuery);
    if(url.isEmpty())
        return;

    // 3.
    createHttpRequest(searchQuery, url);
}

// 1. Build parameters for the URL
SearchQuery Controller::buildQuery(const QString &tag)
{
    SearchQuery::Builder builder(mQueryBuilder);
    auto key = mKeyManager.getKey();

    SearchQueryFactory queryFactory(tag, builder, key);
    return queryFactory.build();
}

// 2. Build the URL using query
QUrl Controller::buildUrl(const SearchQuery &searchQuery)
{
    SearchQueryUrlBuilder urlBuilder(searchQuery);
    return urlBuilder.build();
}

// 3. Create an Http request
void Controller::createHttpRequest(QString &searchTag, QUrl &url)
{
    auto requestType = query.getRequestType();
    auto request = HttpRequestFactory::getInstance()
            .createRequest(requestType);

    if(nullptr == request)
        return;

    request->execRequest(searchTag, url); // << DO YOU REALLY NEED the searchTag string here? It's supposed to identify the returned qnetworkreply. but is there another way?


    searchTag is not needed to be put in execReqest.
            use of httprequest is temporary . create a getter for the  mReply object. or better yet a getter for mReply->readAll()
            i think each httprequest need to be id'd so that when searchQueryFinished is called you can just get request object from Qhash then process it then remove

    // STOP
    // EVERYTHING ABOVE IS LOGICALLY SOUND
    // BELOW MUST BE RETHOUGHT. WHAT EXACTLY IS Tag?
    // What do you want Tag object be?
    // Do you need mTagHash and mSearchRequestList?
    // Can you just create either, not both?
    A Tag object is basically a Plain old cpp object that stores QUrl for these 3 tag roles:
        enum TagRoles {
            BrowserRole = Qt::UserRole + 1,
            Album,
            FullScreen
        };
    and a Rectangle object which contains the coordinates of the POI inside the image.

    A tag object lives in a Tag model which is essentially a qabstractlistmodel.
            1 tagmodel is equal to one tag search string, but contains multiple Tag objects. TagModel has QString mTag which is the tag search string.
            60 for public search
            a tagmodel lives in a hastable QHash<tagSearchString, TagModel>. this is so for easy searching

    Tag mtag(searchTag, mPhotoDefaultSize, query, url); // question is. do you need to be created here now? or somewhere later?
    mTagHash.insert(searchTag, std::move(mtag));
    mSearchRequestList.push_back(std::move(request));
}

// searchQueryFinished() is a SLOT from HttpRequestPublicSearch class
// Control returns to this function following createHttpRequest() above
void Controller::searchQueryFinished(const QString &tag,
                                     const QByteArray &byteArray,
                                     const RequestType &requestType)
{
    if(byteArray.isNull() || byteArray.isEmpty()) {
        cleanup(tag);
        // Something went wrong.
        // Tell QML not to create Tag photo album
        return;
    }

    auto parsedXmlIter = parseXml(byteArray, requestType);
    if(!parsedXmlIter.hasNext()) {
        cleanup(tag);
        return;
    }

    auto photoSize = mTagHash[tag].getPhotoSize();
    auto normalizedUrlIter = getIterator(photoSize, parsedXmlIter, requestType);
    if(!normalizedUrlIter.hasNext()) {
        cleanup(tag);
        return;
    }

    mFileManager.set(tag, photoSize);
    if(!mFileManager.photoDirsExist())
        mFileManager.createPhotoDirs();

    // From here you can check if any item in the iterator already exist
    // If it does then remove from list eg. don't download

    downloadPhotos(tag, normalizedUrlIter, requestType);

    // 6. Save to disk
    // 7. Save path to TagModel or AbstractModelList


    //mTagModelHash[id].setUrlStringIterator(std::move(iterator));
    // Safe to delete mReply from TagModel...
    //mTagModelHash[id].getRequest().reset();
}

QStringListIterator Controller::parseXml(const QByteArray &byteArray,
                                         const RequestType &requestType)
{
    // Need 2 types of XML parser
    // 1. Public search
    // 2. Private search - need to assemble returned list to URLs
    XmlParser parser(byteArray, requestType);
    return parser.parse();
}

QVectorIterator<QPair<Photo::Size, QUrl>> Controller::getIterator(const Photo::DefaultSize &photoSize,
                                                                  const QStringListIterator &iterator,
                                                                  const RequestType &requestType)
{
    UrlTransform transformer(photoSize, iterator, requestType);
    return transformer.transform();
}

void Controller::downloadPhotos(const QString &tag,
                                const QVectorIterator<QPair<Photo::Size, QUrl>> &iterator,
                                const RequestType &requestType)
{
    auto size = getDefaultSize();
    PhotoDownloadManager manager(tag, iterator, size, requestType);
    auto handler = manager.getHandler();
    handler->download();
    mPhotoDataHandlerHash.insert(tag, std::move(handler));
}

void Controller::photoDataHandlerPublicFinished(const QString &tag)
{
    auto photoHandler = std::dynamic_pointer_cast<PhotoDataHandlerPublic>(mPhotoDataHandlerHash[tag]);
    auto browserList = photoHandler->getBrowserFileNameList();
    qDebug() << "SIZE: " << browserList.size();
    foreach(QString s, browserList) {
        qDebug() << "Browser: " << s;
    }

    auto albumList = photoHandler->getAlbumFileNameList();
    qDebug() << "SIZE: " << albumList.size();
    foreach(QString s, albumList) {
        qDebug() << "Album: " << s;
    }
    auto fullScreen = photoHandler->getFullScreenFileNameList();
    qDebug() << "SIZE: " << fullScreen.size();
    foreach(QString s, fullScreen) {
        qDebug() << "FullScreen: " << s;
    }
}

void Controller::setApiKey(QString apiKey)
{
    Q_ASSERT(!apiKey.isNull() && !apiKey.isEmpty());
    mKeyManager.setKey(apiKey);
}

QString Controller::getApiKey() const
{
    auto key = mKeyManager.getKey();
    Q_ASSERT(!key.isNull());

    return key;
}

void Controller::setContentType(QString contentType)
{
    Q_ASSERT(!contentType.isNull() && !contentType.isEmpty());
    mQueryBuilder.setContentType(contentType);
}

void Controller::setPerPage(QString perPage)
{
    Q_ASSERT(!perPage.isNull() && !perPage.isEmpty());
    mQueryBuilder.setPerPage(perPage);
}

void Controller::setPage(QString page)
{
    Q_ASSERT(!page.isNull() && !page.isEmpty());
    mQueryBuilder.setPage(page);
}

void Controller::setPhotoSizeBrowser(QString browserSize)
{
    Q_ASSERT(!browserSize.isNull() && !browserSize.isEmpty());
    mPhotoDefaultSize.Browser = Photo::SizeTable.key(browserSize);
}

void Controller::setPhotoSizeAlbum(QString albumSize)
{
    Q_ASSERT(!albumSize.isNull() && !albumSize.isEmpty());
    mPhotoDefaultSize.Album = Photo::SizeTable.key(albumSize);
}

void Controller::setPhotoSizeFullScreen(QString fullScreenSize)
{
    Q_ASSERT(!fullScreenSize.isNull() && !fullScreenSize.isEmpty());
    mPhotoDefaultSize.FullScreen = Photo::SizeTable.key(fullScreenSize);
}

Photo::DefaultSize Controller::getDefaultSize() const
{
    return mPhotoDefaultSize;
}

void Controller::cleanup(const QString& tag)
{
    mTagHash.remove(tag);
    // also need to find and delete all requests in mHttpRequestList based on their "tag"
}
