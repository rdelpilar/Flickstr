#ifndef PHOTODOWNLOADER_H
#define PHOTODOWNLOADER_H

#include <QObject>
#include "Rss.h"

class PhotoDownloader : public QObject
{
    Q_OBJECT

public:
    explicit PhotoDownloader(QObject* parent = nullptr)
        : QObject(parent) {}
    PhotoDownloader(const std::shared_ptr<QListIterator<QUrl>>&, size_t,
                    const SearchParameters&,
                    const PhotoSize::Size&,
                    const int);
    PhotoDownloader(PhotoDownloader&&) = default;
    PhotoDownloader(const PhotoDownloader&) = default;
    PhotoDownloader& operator=(const PhotoDownloader&) = default;
    PhotoDownloader& operator=(PhotoDownloader&&) = default;
    ~PhotoDownloader() = default;

    void download();

private:
    void createHttpRequestPool();

signals:
    void photoDownloadFinished(const QString&, const QUrl&, const QByteArray&, const size_t, const int);

public slots:
    void photoDownloadFinished(const QUrl&);

private:
    std::shared_ptr<QListIterator<QUrl>> mTransformedUrlsListIter;
    size_t mSize;
    SearchParameters mSearchParams;
    PhotoSize::Size mPhotoSize;
    int mIndex;
    QHash<QUrl, std::shared_ptr<HttpRequest>> mHttpRequestCont;
    QVector<std::shared_ptr<HttpRequest>> mHttpRequestPool;
    const uint8_t DEFAULT_POOL_SIZE = {20};
};

#endif
