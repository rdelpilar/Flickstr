#include "flickstr/TagInfo.h"
#include "flickstr/FileManager.h"

TagInfo::TagInfo()
    : mTag(""),
      mHttpRequest(nullptr),
      mSearchQuery(SearchQuery()),
      mPhotoSize(PhotoSize::Size::Medium_640),
      mAbsolutePath(QStringLiteral("")),
      mUrl(QStringLiteral("")),
      mFilename(QStringLiteral("")),
      mPhotoRect(QRect()),
      mPhotoROIRect(QRect())
{
}

TagInfo::TagInfo(const QString &tag, const std::shared_ptr<HttpRequest> &httpRequest, const SearchQuery &searchQuery, const QUrl& url, const PhotoSize::Size &size)
    : mTag(tag),
      mHttpRequest(httpRequest),
      mSearchQuery(searchQuery),
      mPhotoSize(size),
      mAbsolutePath(QStringLiteral("")),
      mUrl(url),
      mFilename(::UrlToFilePath(url)),
      mPhotoRect(QRect()),
      mPhotoROIRect(QRect())
{
}

QString TagInfo::getTag() const
{
    if(mTag.isNull() || mTag.isEmpty())
        return QString("");
    return mTag;
}

//void TagInfo::setTag(const QString &tag)
//{
//    mTag = tag;
//}

std::shared_ptr<HttpRequest> TagInfo::getHttpRequest() const
{
    return mHttpRequest;
}

//void TagInfo::setHttpRequest(const std::shared_ptr<HttpRequest> &httpRequest)
//{
//    mHttpRequest = httpRequest;
//}

SearchQuery TagInfo::getSearchQuery() const
{
    return mSearchQuery;
}

//void TagInfo::setSearchQuery(const SearchQuery &searchQuery)
//{
//    mSearchQuery = searchQuery;
//}

PhotoSize::Size TagInfo::getPhotoSize() const
{
    return mPhotoSize;
}

QString TagInfo::getAbsolutePath() const
{
    if(mAbsolutePath.isNull() || mAbsolutePath.isEmpty())
        return QString("");
    return mAbsolutePath;
}

void TagInfo::setAbsolutePath(const QString &absolutePath)
{
    mAbsolutePath = absolutePath;
}

QUrl TagInfo::getUrl() const
{
    if(mUrl.isEmpty())
        return QUrl("");
    return mUrl;
}

QString TagInfo::getFilename() const
{
    if(mFilename.isNull() || mFilename.isEmpty())
        return QString("");
    return mFilename;
}

QRect TagInfo::getPhotoRect() const
{
    if(mPhotoRect.isNull())
        return QRect(0,0,0,0);
    return mPhotoRect;
}

void TagInfo::setPhotoRect(const QRect &photoRect)
{
    mPhotoRect = photoRect;
}

QRect TagInfo::getPhotoROIRect() const
{
    return mPhotoROIRect;
}

void TagInfo::setPhotoROIRect(const QRect &photoROIRect)
{
    mPhotoROIRect = photoROIRect;
}
