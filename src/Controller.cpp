#include "flickstr/Controller.h"
#include "flickstr/SearchParametersHandler.h"
#include "flickstr/UrlBuilder.h"
#include "flickstr/HttpRequestFactory.h"
#include "flickstr/XmlParserHandler.h"
#include "flickstr/UrlTransformerHandler.h"
#include "flickstr/PhotoDownloader.h"

#include <QPixmap>
#include <QRect>
#include <QDebug>

Controller::Controller(QObject *parent)
    : QObject(parent),
      mKeyManager(ApiKeyManager()),
      mDownloaderCont(QHash<int, std::shared_ptr<DownloadHandler>>()),
      mListModel(std::make_shared<RssListModel>()),
      mDownloadProgressHandler(DownloadProgressHandler()),
      mParamsBuilder(SearchParameters::Builder()),
      //mPhotoSize(PhotoSize::Size::Medium_640)
      mPhotoSize(PhotoSize::Size::LargeSquare_150)

      //mDbManager(DatabaseManager()),
      //mFileManager(FileManager()),
      //mSqlModel(new TagSqlModel(nullptr, mDbManager.getTableName()))
{
}

Controller::~Controller()
{
}

QObject* Controller::provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    static Controller mInstance;

    QQmlEngine::setObjectOwnership(&mInstance, QQmlEngine::CppOwnership);

    return &mInstance;
}

void Controller::init(QQmlApplicationEngine *engine)
{
    mEngine = engine;
    QQmlEngine::setObjectOwnership(mEngine, QQmlEngine::CppOwnership);

    mEngine->rootContext()->setContextProperty(QStringLiteral("RssListModel"), mListModel.get());
    QQmlEngine::setObjectOwnership(mListModel.get(), QQmlEngine::CppOwnership);

    mEngine->rootContext()->setContextProperty(QStringLiteral("DownloadProgressHandler"), &mDownloadProgressHandler);
    QQmlEngine::setObjectOwnership(&mDownloadProgressHandler, QQmlEngine::CppOwnership);

    qmlRegisterSingletonType<Controller>("ControllerLib",
                                         1,
                                         0,
                                         "Controller",
                                         &Controller::provider);

    mEngine->addImageProvider(QStringLiteral("ImageProvider"), new RssModelImageProvider(mListModel));

    mEngine->load(QUrl("qrc:///CoreQml/main.qml"));
}

void Controller::createDummyListModel()
{
    mListModel->createDummyListModel();
}

// setTag replaces contents of mListModel at index 'index' whether empty or not
void Controller::setTag(int index, QString tagLabel)
{
    if(index < 0) return;

    if(!mListModel->rssModelTagEmpty(index))
        mListModel->resetRssModel(index);

    mListModel->setRssModelTag(index, tagLabel);

    execRequest(tagLabel, index);
}

void Controller::execRequest(const QString &tagLabel, const int index)
{
    auto searchParams = buildParameters(tagLabel);
    if(!searchParams.isValid()) return;

    auto url = buildUrl(searchParams);
    if(url.isEmpty()) return;

    xmlDownloadStart(searchParams, url, index);
}

SearchParameters Controller::buildParameters(const QString &tagLabel)
{
    SearchParameters::Builder builder(mParamsBuilder);
    auto key = mKeyManager.getKey();

    SearchParametersHandler paramsHandler(tagLabel, builder, key);
    return paramsHandler.build();
}

QUrl Controller::buildUrl(const SearchParameters &searchParams)
{
    UrlBuilder builder(searchParams);
    return builder.build();
}

// Download Xml
void Controller::xmlDownloadStart(const SearchParameters &searchParams, const QUrl &url, const int index)
{
    auto xmlDownloader = std::make_shared<DownloadHandler>(searchParams, url, index);
    xmlDownloader->download();
    mDownloaderCont.insert(index, std::move(xmlDownloader));
}

// Finished downloading Xml
void Controller::xmlDownloadFinished(const SearchParameters &searchParams, const QByteArray &byteArray, const int index)
{
    if(byteArray.size() <= 0) {
        mListModel->removeRow(index);
        mDownloaderCont.remove(index);
        return;
    }

    auto params(searchParams);
    auto parsedXmlIter = parseXml(searchParams, byteArray);

    UrlTransformerHandler transformerHandler(parsedXmlIter, mPhotoSize, searchParams.getRequestType());
    auto transformedListIter = transformerHandler.transform();
    auto size = transformerHandler.size();

    if(!transformedListIter->hasNext()) {
        mListModel->removeRow(index);
        mDownloaderCont.remove(index);
        return;
    }

    mDownloaderCont.remove(index);

    photoDownloadStart(params, transformedListIter, size, index);
}

// This xml handler needs to be able to keep track of the photos attributes from the xmlparserprivate object
// or SearchParmeters, or XmlParserPrivate. Choose.
std::shared_ptr<QStringListIterator> Controller::parseXml(const SearchParameters &searchParams,
                                                          const QByteArray &byteArray)
{
    auto requestType(searchParams.getRequestType());

    XmlParserHandler parser(byteArray, requestType);
    return parser.parse();
}

// Start downloading photos
void Controller::photoDownloadStart(const SearchParameters &searchParams,
                                    const std::shared_ptr<QListIterator<QUrl>> &transformedUrlsIter,
                                    const size_t size,
                                    const int index)
{
    initDownloadProgress(index);
    //mImageProvider.setRssModelIndex(index);

    auto photoDownloader = std::make_shared<DownloadHandler>(searchParams, transformedUrlsIter, size, mPhotoSize, index);
    photoDownloader->download();

    mDownloaderCont.insert(index, std::move(photoDownloader));
}

// Finished downloading a photo
void Controller::photoDownloadFinished(const QString &tag,
                                       const QUrl &url,
                                       const QByteArray &byteArray,
                                       const size_t size,
                                       const int index)
{
    if(url.isEmpty() || byteArray.isEmpty())
        return;

    Rss rss(url, byteArray);
    setPhotoRect(rss);
    mListModel->addRss(index, std::move(rss));

    updateDownloadProgress(index, size);

    if(mListModel->getRssModelSize(index) == size) {
        mDownloaderCont.remove(index);
        updateDownloadProgressFinished(index);
    }

    // Don't forget to delete items from mProgressDownloadHandler
    // when deleting an RssModel

    // REFACTOR: Just delete the request but not the query
    // THE QByteArray is not deleted. It is retained in httpRequest object
    // Figure out a way to delete it.
    // YOu will need to reuse the query.
    // You also need the info from this object: mPhotosAttributes
    // which gives you the page, pages, perpages, and total variables
    //mDownloadHandlerHash.remove(tag);

}

void Controller::initDownloadProgress(const int index)
{
    mDownloadProgressHandler.createDownloadProgress(index);
    mDownloadProgressHandler.setVisible(index, true);
}

void Controller::updateDownloadProgress(const int index, const size_t size)
{
    auto pos = mDownloadProgressHandler.getValue(index);
    pos += (1.0 / size);
    mDownloadProgressHandler.setValue(index, pos);
}

void Controller::updateDownloadProgressFinished(const int index)
{
    mDownloadProgressHandler.setVisible(index, false);
}

void Controller::setApiKey(QString apiKey)
{
    mKeyManager.setKey(apiKey);
}

void Controller::setPhotoRect(Rss& rss)
{
    QPixmap p;
    p.loadFromData(*rss.getData());
    if(p.isNull()) return;
    rss.setPhotoRect(p.rect());
    qDebug() << "size: " << p.rect().width() << "x" << p.rect().height();
}

QString Controller::getApiKey() const
{
    auto key = mKeyManager.getKey();
    if(key.isNull()) return QString("");

    return key;
}

void Controller::setContentType(QString contentType)
{
    if(contentType.isNull() || contentType.isEmpty()) return;

    mParamsBuilder.setContentType(contentType);
}

void Controller::setPerPage(QString perPage)
{
    if(perPage.isNull() || perPage.isEmpty()) return;

    mParamsBuilder.setPerPage(perPage);
}

void Controller::setPage(QString page)
{
    if(page.isNull() || page.isEmpty())
        return;
    mParamsBuilder.setPage(page);
}

void Controller::setPhotoSize(QString fullScreenSize)
{
    if(fullScreenSize.isNull() || fullScreenSize.isEmpty()) return;

    mPhotoSize = ::SizeLabelToEnum(fullScreenSize);
}

PhotoSize::Size Controller::getPhotoSize() const
{
    return mPhotoSize;
}
