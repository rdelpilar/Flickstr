#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkReply>
#include <QUrl>
#include <memory>

enum class RequestType { PUBLIC_SEARCH = 0,
                         PRIVATE_SEARCH,
                         PHOTO_DOWNLOAD
                       };

class HttpRequest : public QObject
{
    Q_OBJECT

public:
    HttpRequest() = default;
    HttpRequest(const std::shared_ptr<QNetworkAccessManager>&);
    HttpRequest(HttpRequest&&) = delete;
    HttpRequest(const HttpRequest&) = delete;
    HttpRequest& operator=(const HttpRequest&) = delete;
    HttpRequest& operator=(const HttpRequest&&) = delete;
    ~HttpRequest() = default;

    void execRequest(const QUrl &url);
    QByteArray getData();
    QNetworkReply::NetworkError& getError();
    QList<QSslError>& getSslErrorList();

private slots:
    void downloadError(QNetworkReply::NetworkError);
    void sslErrors(QList<QSslError>);
    void requestFinished();

signals:
    void httpRequestFinished(const QUrl&);

private:
    std::shared_ptr<QNetworkAccessManager> mAccessManager;
    std::unique_ptr<QNetworkReply> mNetworkReply;
    QNetworkReply::NetworkError mNetworkError;
    QList<QSslError> mSslErrorList;
    QByteArray mByteArray;
    QUrl mUrl;
};

#endif
