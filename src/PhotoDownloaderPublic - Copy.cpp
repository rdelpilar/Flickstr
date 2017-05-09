#include "flickstr/PhotoDownloaderPublic.h"
#include "flickstr/HttpRequestFactory.h"
#include "flickstr/Controller.h"

PhotoDownloaderPublic::PhotoDownloaderPublic(const QHash<QUrl, TagInfo>::const_iterator &tagIter, const QListIterator<QUrl> &transformedIter)
    : mTagIter(tagIter),
      mTransformedListIter(transformedIter),
      mTagInfoHash(QHash<QUrl, TagInfo>()),
      mCounter(0)
{
    connect(this,
            SIGNAL(photoDownloaderFinished(const std::shared_ptr<QMutableHashIterator<QUrl, TagInfo>>)),
            Controller::provider(NULL, NULL),
            SLOT(photoDownloaderFinished(const std::shared_ptr<QMutableHashIterator<QUrl, TagInfo>>)),
            static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection));
}

void PhotoDownloaderPublic::download()
{
    if(mTagIter.key().isEmpty())
        return;

    auto tag = mTagIter->getTag();
    if(tag.isNull() || tag.isEmpty())
        return;

    while(mTransformedListIter.hasNext()) {
        auto item = mTransformedListIter.next();

        auto request = HttpRequestFactory::getInstance().createRequest(requestType);
        if(nullptr == request)
            continue;

        connect(request.get(),
                SIGNAL(photoDownloadFinished(const QUrl&)),
                this,
                SLOT(photoDownloadFinished(const QUrl&)),
                static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection));

        QUrl url(item.key());
        request->execRequest(url);

        TagInfo tagInfo(tag, std::move(request), SearchQuery(), url, item.value());
        mTagInfoHash.insert(std::move(url), std::move(tagInfo));
    }
}

// Callback
void PhotoDownloaderPublic::photoDownloadFinished(const QUrl& url)
{
    QHash<QUrl, TagInfo>::iterator tagIter = mTagInfoHash.find(url);
    if(tagIter == mTagInfoHash.end())
        return;

    auto error = tagIter->getHttpRequest()->getError();
    if(QNetworkReply::NoError != error) {
        mTagInfoHash.erase(tagIter);
        return;
    }

    auto sslError = tagIter->getHttpRequest()->getSslErrorList();
    if(!sslError.isEmpty()) {
        mTagInfoHash.erase(tagIter);
        return;
    }

    auto byteArraySize = tagIter->getHttpRequest()->getByteArraySize();
    if(byteArraySize <= 0) {
        mTagInfoHash.erase(tagIter);
        return;
    }

    mCounter++;

    if(mTagInfoHash.size() == mCounter) {
        emit photoDownloaderFinished(std::make_shared<QMutableHashIterator<QUrl, TagInfo>>(mTagInfoHash));
    }
}
