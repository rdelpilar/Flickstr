#ifndef PHOTODOWNLOADER_H
#define PHOTODOWNLOADER_H

#include <QObject>
#include "HttpRequest.h"

class PhotoDownloader : public QObject
{
    Q_OBJECT

public:
    PhotoDownloader() = default;
    PhotoDownloader(PhotoDownloader&&) = delete;
    PhotoDownloader(const PhotoDownloader&) = delete;
    PhotoDownloader& operator=(const PhotoDownloader&) = delete;
    PhotoDownloader& operator=(const PhotoDownloader&&) = delete;
    virtual ~PhotoDownloader() = default;

    virtual void download() = 0;
};

#endif
