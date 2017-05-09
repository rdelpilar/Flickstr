#include "flickstr/Rss.h"
#include "flickstr/FileManager.h"

Rss::Rss(const QUrl& url,
         const QByteArray &byteArray,
         QObject *parent)
    : QObject(parent),
      mUrl(url),
      mSize(byteArray.size()),
      mByteArray(std::make_shared<QByteArray>(byteArray)),
      mFilename(::UrlToFilePath(url)),
      mAbsolutePath(QStringLiteral("")),
      mPhotoRect(QRect()),
      mPhotoROIRect(QRect())
{
}

Rss::Rss(Rss &&rhs) noexcept
    : mUrl(rhs.mUrl),
      mSize(rhs.mSize),
      mByteArray(rhs.mByteArray),
      mFilename(rhs.mFilename),
      mAbsolutePath(rhs.mAbsolutePath),
      mPhotoRect(rhs.mPhotoRect),
      mPhotoROIRect(rhs.mPhotoROIRect)
{
}

Rss::Rss(const Rss &rhs) noexcept
    : QObject(nullptr),
      mUrl(rhs.mUrl),
      mSize(rhs.mSize),
      mByteArray(rhs.mByteArray),
      mFilename(rhs.mFilename),
      mAbsolutePath(rhs.mAbsolutePath),
      mPhotoRect(rhs.mPhotoRect),
      mPhotoROIRect(rhs.mPhotoROIRect)
{
}

Rss& Rss::operator=(const Rss &rhs) noexcept
{
    if(this == &rhs)
        return *this;
    Rss tmp(rhs);
    *this = std::move(tmp);
    return *this;
}

Rss& Rss::operator=(Rss &&rhs) noexcept
{
    if(this == &rhs)
        return *this;
    Rss tmp(rhs);
    *this = std::move(tmp);
    return *this;
}

QUrl Rss::getUrl() const
{
    return mUrl;
}

qint64 Rss::getDataSize() const
{
    return mSize;
}

std::shared_ptr<QByteArray> Rss::getData()
{
    return mByteArray;
}

QString Rss::getFilename() const
{
    return mFilename;
}

QString Rss::getAbsolutePath() const
{
    return mAbsolutePath;
}

QRect Rss::getPhotoRect() const
{
    return mPhotoRect;
}

void Rss::setPhotoRect(const QRect &photoRect)
{
    mPhotoRect = photoRect;
}

QRect Rss::getPhotoROIRect() const
{
    return mPhotoROIRect;
}

void Rss::setPhotoROIRect(const QRect &rect)
{
    mPhotoROIRect = rect;
    emit photoROIRectChanged(rect);
}

void Rss::setAbsolutePath(const QString &absolutePath)
{
    mAbsolutePath = absolutePath;
}
