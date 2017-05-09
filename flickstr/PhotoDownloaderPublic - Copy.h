#ifndef PHOTODOWNLOADERPUBLIC_H
#define PHOTODOWNLOADERPUBLIC_H

#include <QObject>
#include <QHash>
#include <memory>

#include "PhotoSize.h"
#include "TagInfo.h"

class PhotoDownloaderPublic
{
    Q_OBJECT

public:
    PhotoDownloaderPublic() = default;
    PhotoDownloaderPublic(const QHash<QUrl, TagInfo>::const_iterator&,
                          const QListIterator<QUrl>&);
    PhotoDownloaderPublic(PhotoDownloaderPublic&&) = delete;
    PhotoDownloaderPublic(const PhotoDownloaderPublic&) = delete;
    PhotoDownloaderPublic& operator=(const PhotoDownloaderPublic&) = delete;
    PhotoDownloaderPublic& operator=(const PhotoDownloaderPublic&&) = delete;
    ~PhotoDownloaderPublic() = default;

    void download();

signals:
    void photoDownloaderFinished(std::shared_ptr<QMutableHashIterator<QUrl, TagInfo>>);

public slots:
    void photoDownloadFinished(const QUrl&);

private:
    QHash<QUrl, TagInfo>::const_iterator mTagIter;
    QListIterator<QUrl> mTransformedListIter;
    QHash<QUrl, TagInfo> mTagInfoHash;
    uint8_t mCounter;
};

#endif
