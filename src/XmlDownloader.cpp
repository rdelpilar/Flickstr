#include "flickstr/XmlDownloader.h"
#include "flickstr/HttpRequestFactory.h"
#include "flickstr/Controller.h"

XmlDownloader::XmlDownloader(const SearchParameters &searchParams, const QUrl& url, const int index)
    : mSearchParams(searchParams),
      mUrl(url),
      mIndex(index),
      mRequest(nullptr)
{
}

void XmlDownloader::download()
{
    if(mUrl.isEmpty())
        return;

    if(!mSearchParams.isValid())
        return;

    mRequest = HttpRequestFactory::getInstance().createRequest();
    if(nullptr == mRequest)
        return;

    connect(mRequest.get(),
            SIGNAL(httpRequestFinished(const QUrl&)),
            this,
            SLOT(xmlDownloadFinished(const QUrl&)),
            static_cast<Qt::ConnectionType>(Qt::DirectConnection));

    mRequest->execRequest(mUrl);
}

// Callback
void XmlDownloader::xmlDownloadFinished(const QUrl& url)
{
    auto error = mRequest->getError();
    if(QNetworkReply::NoError != error) return;

    auto sslError = mRequest->getSslErrorList();
    if(!sslError.isEmpty()) return;

    emit xmlDownloadFinished(mSearchParams, mRequest->getData(), mIndex);
}
