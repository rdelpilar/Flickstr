#ifndef TAGINFO_H
#define TAGINFO_H

#include <QObject>
#include <QRect>
#include <QFileInfo>
#include <memory>
#include "SearchParameters.h"
#include "HttpRequest.h"
#include "PhotoSize.h"

// Need this: mPhotosAttributes from XmlParserPrivate

inline QString UrlToFilePath(const QUrl &url)
{
    QFileInfo fileInfo(url.toString());
    return fileInfo.fileName();
}

class Rss : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QRect roi READ getPhotoROIRect WRITE setPhotoROIRect NOTIFY photoROIRectChanged)

public:
    Rss(QObject *parent = 0);
    Rss(const QUrl&, const QByteArray&, QObject *parent = 0);
    Rss(Rss&&) noexcept;
    Rss(const Rss&) noexcept;
    Rss& operator=(const Rss&) noexcept;
    Rss& operator=(Rss&&) noexcept;
    ~Rss() = default;

    QUrl getUrl() const;
    qint64 getDataSize() const;
    std::shared_ptr<QByteArray> getData();
    QString getFilename() const;
    QRect getPhotoRect() const;
    QString getAbsolutePath() const;
    QRect getPhotoROIRect() const;
    void setPhotoROIRect(const QRect&);

    void setAbsolutePath(const QString&);
    void setPhotoRect(const QRect&);

signals:
    void photoROIRectChanged(QRect);

private:
    QUrl mUrl;
    qint64 mSize;
    std::shared_ptr<QByteArray> mByteArray;
    QString mFilename;
    QString mAbsolutePath;
    QRect mPhotoRect;
    QRect mPhotoROIRect;
};

#endif
