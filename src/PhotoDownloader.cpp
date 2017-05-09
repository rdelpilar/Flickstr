#include "flickstr/PhotoDownloader.h"
#include "flickstr/HttpRequestFactory.h"
#include "flickstr/Controller.h"

PhotoDownloader::PhotoDownloader(const std::shared_ptr<QListIterator<QUrl>> &transformedIter,
                                 const size_t size,
                                 const SearchParameters &searchParams,
                                 const PhotoSize::Size &photoSize,
                                 const int index)
    : mTransformedUrlsListIter(transformedIter),
      mSize(size),
      mSearchParams(searchParams),
      mPhotoSize(photoSize),
      mIndex(index),
      mHttpRequestCont(QHash<QUrl, std::shared_ptr<HttpRequest>>()),
      mHttpRequestPool(QVector<std::shared_ptr<HttpRequest>>())
{
    createHttpRequestPool();
}

// This needs to be run on a separate thread
// Adjust the pool size according to the number of per_page
void PhotoDownloader::createHttpRequestPool()
{
    for(size_t i = 0; i < DEFAULT_POOL_SIZE; ++i) {
        auto request = HttpRequestFactory::getInstance().createRequest();
        if(request != nullptr)
            mHttpRequestPool.push_back(std::move(request));
    }
}

// Signal
void PhotoDownloader::download()
{
    while(mTransformedUrlsListIter->hasNext()) {
        auto url = mTransformedUrlsListIter->next();

        if(mHttpRequestPool.isEmpty())
            createHttpRequestPool();

        auto request = mHttpRequestPool.takeFirst();

        connect(request.get(),
                SIGNAL(httpRequestFinished(const QUrl&)),
                this,
                SLOT(photoDownloadFinished(const QUrl&)),
                static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection));

        request->execRequest(url);
        mHttpRequestCont.insert(std::move(url), std::move(request));
    }
}

// Return single item callback
void PhotoDownloader::photoDownloadFinished(const QUrl &url)
{
    QHash<QUrl, std::shared_ptr<HttpRequest>>::iterator iter = mHttpRequestCont.find(url);
    if(iter == mHttpRequestCont.end())
        return;

    emit photoDownloadFinished(mSearchParams.getTag(), url, std::move(iter.value()->getData()), mSize, mIndex);
}
