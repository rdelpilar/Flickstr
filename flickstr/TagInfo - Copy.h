#ifndef TAGINFO_H
#define TAGINFO_H

#include <QRect>
#include <QFileInfo>
#include <memory>
#include "SearchQuery.h"
#include "HttpRequest.h"
#include "PhotoSize.h"

// Need this: mPhotosAttributes from XmlParserPrivate

inline QString UrlToFilePath(const QUrl &url)
{
    QFileInfo fileInfo(url.toString());
    return fileInfo.fileName();
}

class TagInfo
{
public:
    TagInfo();
    TagInfo(const QString&, const std::shared_ptr<HttpRequest>&, const SearchQuery&, const QUrl&, const PhotoSize::Size&);
    TagInfo(TagInfo&&) = default;
    TagInfo(const TagInfo&) = default;
    TagInfo& operator=(const TagInfo&) = default;
    TagInfo& operator=(TagInfo&&) = default;
    ~TagInfo() = default;

    QString getTag() const;
    std::shared_ptr<HttpRequest> getHttpRequest() const;
    SearchQuery getSearchQuery() const;
    QUrl getUrl() const;
    QString getFilename() const;
    PhotoSize::Size getPhotoSize() const;
    QRect getPhotoRect() const;
    QString getAbsolutePath() const;
    QRect getPhotoROIRect() const;

    void setAbsolutePath(const QString&);
    void setPhotoRect(const QRect&);
    void setPhotoROIRect(const QRect&);

private:
    QString mTag;
    std::shared_ptr<HttpRequest> mHttpRequest;
    SearchQuery mSearchQuery;
    PhotoSize::Size mPhotoSize;
    QString mAbsolutePath;
    QUrl mUrl;
    QString mFilename;
    QRect mPhotoRect;
    QRect mPhotoROIRect;
};

#endif
