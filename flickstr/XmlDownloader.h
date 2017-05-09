#ifndef XMLDOWNLOADER_H
#define XMLDOWNLOADER_H

#include <QObject>
#include <memory>
#include "SearchParameters.h"
#include "HttpRequest.h"

class XmlDownloader : public QObject
{
    Q_OBJECT

public:
    explicit XmlDownloader(QObject* parent = nullptr) : QObject(parent) {}
    XmlDownloader(const SearchParameters&, const QUrl&, const int);
    XmlDownloader(XmlDownloader&&) = default;
    XmlDownloader(const XmlDownloader&) = default;
    XmlDownloader& operator=(const XmlDownloader&) = default;
    XmlDownloader& operator=(XmlDownloader&&) = default;
    ~XmlDownloader() = default;

    void download();

signals:
    void xmlDownloadFinished(const SearchParameters&, const QByteArray&, const int);

public slots:
    void xmlDownloadFinished(const QUrl&);

private:
    SearchParameters mSearchParams;
    QUrl mUrl;
    int mIndex;
    std::shared_ptr<HttpRequest> mRequest;
};

#endif
