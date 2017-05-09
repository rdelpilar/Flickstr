#include "flickstr/HttpRequest.h"
#include "flickstr/Controller.h"

HttpRequest::HttpRequest(const std::shared_ptr<QNetworkAccessManager> &accessManager)
    : mAccessManager(accessManager),
      mNetworkReply(nullptr),
      mNetworkError(QNetworkReply::NoError),
      mSslErrorList(QList<QSslError>()),
      mByteArray(QByteArray()),
      mUrl(QStringLiteral(""))
{
}

void HttpRequest::execRequest(const QUrl &url)
{
    if(!url.isValid())
        return;

    mUrl = url;

    QNetworkRequest request(mUrl);
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("User-Agent", "Flickstr 1.0");
    mNetworkReply.reset(mAccessManager->get(request));

    connect(mNetworkReply.get(),
            SIGNAL(error(QNetworkReply::NetworkError)),
            this,
            SLOT(downloadError(QNetworkReply::NetworkError)),
            static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection));

    connect(mNetworkReply.get(),
            SIGNAL(sslErrors(QList<QSslError>)),
            this,
            SLOT(sslErrors(QList<QSslError>)),
            static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection));

    connect(mNetworkReply.get(),
            SIGNAL(finished()),
            this,
            SLOT(requestFinished()),
            static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection));
}

void HttpRequest::downloadError(QNetworkReply::NetworkError error)
{
    mNetworkError = error;
}

void HttpRequest::sslErrors(QList<QSslError> sslErrorList)
{
    mSslErrorList = sslErrorList;
}

void HttpRequest::requestFinished()
{
    if(nullptr == mNetworkReply) {
        return;
    }

    emit httpRequestFinished(mUrl);
}

QByteArray HttpRequest::getData()
{
    return mNetworkReply->readAll();
}

QList<QSslError>& HttpRequest::getSslErrorList()
{
    return mSslErrorList;
}

QNetworkReply::NetworkError& HttpRequest::getError()
{
    return mNetworkError;
}
