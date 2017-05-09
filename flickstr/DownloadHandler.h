#ifndef DOWNLOADHANDLER_H
#define DOWNLOADHANDLER_H

#include <QObject>
#include "SearchParameters.h"
#include "XmlDownloader.h"
#include "PhotoDownloader.h"

class DownloadHandler : public QObject
{
    Q_OBJECT

public:
    DownloadHandler() = default;
    DownloadHandler(const SearchParameters&, const QUrl&, const int);
    DownloadHandler(const SearchParameters&, const std::shared_ptr<QListIterator<QUrl>>&, const size_t, const PhotoSize::Size&, const int);
    DownloadHandler(DownloadHandler&&) = delete;
    DownloadHandler(const DownloadHandler&) = delete;
    DownloadHandler& operator=(const DownloadHandler&) = delete;
    DownloadHandler& operator=(const DownloadHandler&&) = delete;
    ~DownloadHandler() = default;

    void download();

private:
    template <typename T>
    void download(T&) const;

private:
    SearchParameters mSearchParams;
    QUrl mUrl;
    int mIndex;
    std::shared_ptr<QListIterator<QUrl>> mUrlListIterator;
    size_t mSize;
    PhotoSize::Size mPhotoSize;
    RequestType mRequestType;
    std::shared_ptr<XmlDownloader> mXmlDownloader;
    std::shared_ptr<PhotoDownloader> mPhotoDownloader;
};

#endif
