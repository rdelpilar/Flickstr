#ifndef HTTPREQUESTPUBLICSEARCH_H
#define HTTPREQUESTPUBLICSEARCH_H

#include <memory>
#include "HttpRequest.h"

class HttpRequestPublicSearch : public HttpRequest
{
    Q_OBJECT

public:
    HttpRequestPublicSearch() = default;
    HttpRequestPublicSearch(const std::shared_ptr<QNetworkAccessManager>&);
    HttpRequestPublicSearch(HttpRequestPublicSearch&&) = delete;
    HttpRequestPublicSearch(const HttpRequestPublicSearch&) = delete;
    HttpRequestPublicSearch& operator=(const HttpRequestPublicSearch&) = delete;
    HttpRequestPublicSearch& operator=(const HttpRequestPublicSearch&&) = delete;
    virtual ~HttpRequestPublicSearch() = default;

    virtual void execRequest(const QUrl&);
    virtual QByteArray& getData();
    virtual QNetworkReply::NetworkError& getError();
    virtual QList<QSslError>& getSslErrorList();
    virtual qint64& getByteArraySize();

protected slots:
    void downloadError(QNetworkReply::NetworkError);
    void sslErrors(QList<QSslError>);
    void updateProgress(qint64, qint64);
    void requestFinished();

signals:
    void searchQueryFinished(const QUrl&);

private:
    std::shared_ptr<QNetworkAccessManager> mAccessManager;
    std::unique_ptr<QNetworkReply> mNetworkReply;
    QNetworkReply::NetworkError mNetworkError;
    QList<QSslError> mSslErrorList;
    QByteArray mByteArray;
    qint64 mByteArraySize;
    QUrl mUrl;
};

#endif
