#include "flickstr/HttpRequestPhotoDownload.h"
#include "flickstr/PhotoDownloader.h"
#include "flickstr/Controller.h"



// DUPLICATE CODE WITH HttpRequestPublicSearch
// USE TEMPLATES HERE! eg. static polymorphism







HttpRequestPhotoDownload::HttpRequestPhotoDownload(const std::shared_ptr<QNetworkAccessManager> &accessManager)
    : mAccessManager(accessManager),
      mNetworkReply(nullptr),
      mNetworkError(QNetworkReply::NoError),
      mSslErrorList(QList<QSslError>()),
      mByteArray(QByteArray()),
      mByteArraySize(0),
      mUrl("")
{
}

void HttpRequestPhotoDownload::execRequest(const QUrl &url)
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

void HttpRequestPhotoDownload::downloadError(QNetworkReply::NetworkError error)
{
    mNetworkError = error;
}

void HttpRequestPhotoDownload::sslErrors(QList<QSslError> sslErrorList)
{
    mSslErrorList = sslErrorList;
}

void HttpRequestPhotoDownload::updateProgress(qint64, qint64)
{

}

void HttpRequestPhotoDownload::requestFinished()
{
    if(nullptr == mNetworkReply)
        return;

    emit photoDownloadFinished(mUrl);
}

QList<QSslError>& HttpRequestPhotoDownload::getSslErrorList()
{
    return mSslErrorList;
}

QByteArray& HttpRequestPhotoDownload::getData()
{
    mByteArray = mNetworkReply->readAll();
    return mByteArray;
}

qint64& HttpRequestPhotoDownload::getByteArraySize()
{
    mByteArraySize = mNetworkReply->size();
    return mByteArraySize;
}

QNetworkReply::NetworkError& HttpRequestPhotoDownload::getError()
{
    return mNetworkError;
}
