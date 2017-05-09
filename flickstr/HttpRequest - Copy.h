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
    HttpRequest(HttpRequest&&) = delete;
    HttpRequest(const HttpRequest&) = delete;
    HttpRequest& operator=(const HttpRequest&) = delete;
    HttpRequest& operator=(const HttpRequest&&) = delete;
    virtual ~HttpRequest() = default;

    virtual void execRequest(const QUrl &url) = 0;
    virtual QByteArray& getData() = 0;
    virtual QNetworkReply::NetworkError& getError() = 0;
    virtual QList<QSslError>& getSslErrorList() = 0;
    virtual qint64& getByteArraySize() = 0;
};

#endif
