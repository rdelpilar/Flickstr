#include "flickstr/HttpRequestPublicSearch.h"
#include "flickstr/Controller.h"




// DUPLICATE CODE WITH HttpRequestPublicPhoto
// USE TEMPLATES HERE! eg. static polymorphism



HttpRequestPublicSearch::HttpRequestPublicSearch(const std::shared_ptr<QNetworkAccessManager> &accessManager)
    : mAccessManager(accessManager),
      mNetworkReply(nullptr),
      mNetworkError(QNetworkReply::NoError),
      mSslErrorList(QList<QSslError>()),
      mByteArray(QByteArray()),
      mByteArraySize(0),
      mUrl("")
{
    connect(this,
            SIGNAL(searchQueryFinished(const QUrl&)),
            Controller::provider(NULL, NULL),
            SLOT(searchQueryFinished(const QUrl&)),
            static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection));
}

void HttpRequestPublicSearch::execRequest(const QUrl &url)
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
            SIGNAL(downloadProgress(qint64, qint64)),
            this,
            SLOT(updateProgress(qint64, qint64)),
            static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection));

    connect(mNetworkReply.get(),
            SIGNAL(finished()),
            this,
            SLOT(requestFinished()),
            static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::DirectConnection));
}

void HttpRequestPublicSearch::downloadError(QNetworkReply::NetworkError error)
{
    mNetworkError = error;
}

void HttpRequestPublicSearch::sslErrors(QList<QSslError> sslErrorList)
{
    mSslErrorList = sslErrorList;
}

void HttpRequestPublicSearch::updateProgress(qint64, qint64)
{
}

void HttpRequestPublicSearch::requestFinished()
{
    if(nullptr == mNetworkReply)
        return;

    emit searchQueryFinished(mUrl);
}

QByteArray& HttpRequestPublicSearch::getData()
{
    mByteArray = mNetworkReply->readAll();
    mByteArraySize = 0;
    return mByteArray;
}

qint64& HttpRequestPublicSearch::getByteArraySize()
{
    mByteArraySize = mNetworkReply->size();
    return mByteArraySize;
}

QList<QSslError>& HttpRequestPublicSearch::getSslErrorList()
{
    return mSslErrorList;
}

QNetworkReply::NetworkError& HttpRequestPublicSearch::getError()
{
    return mNetworkError;
}

