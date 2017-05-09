#include "flickstr/UrlTransformerPublic.h"
#include <QFileInfo>
#include <QVectorIterator>

UrlTransformerPublic::UrlTransformPublic(const QStringListIterator &iterator,
                                         const PhotoSize::Size& photoSize)
    : mIterator(iterator),
      mPhotoSize(photoSize)
{
}

void UrlTransformerPublic::transform()
{
    QString url;

    while(mIterator.hasNext()) {
        QFileInfo fileInfo = mIterator.next();

        if(fileInfo.suffix().compare("jpg", Qt::CaseInsensitive) != 0)
            continue;

        // We expect a "_m" photo size from the list
        auto suffix = mDefaultPhotoSize.album.getSuffix();
        if(!fileInfo.baseName().endsWith(suffix))
            continue;

        // Create 3 different URLs
        // 1. Album size
        auto size = mDefaultPhotoSize.album.getSize();
        mUrlHash.insert(QUrl(fileInfo.filePath()), std::shared_ptr<PhotoSize>(new PhotoSizeAlbum(size, suffix)));

        // Remove the "_x" substring from the url
        auto leftLen = fileInfo.baseName().size() - mDefaultPhotoSize.album.getSuffix().size();
        if(leftLen <= 0) continue;

        // 2. Browser size
        suffix = mDefaultPhotoSize.browser.getSuffix();
        size = mDefaultPhotoSize.browser.getSize();
        url = QString("%1/%2%3.%4")
                .arg(fileInfo.path())
                .arg(fileInfo.baseName()
                     .left(leftLen))
                .arg(mDefaultPhotoSize.browser.getSuffix())
                .arg(fileInfo.suffix());
        mUrlHash.insert(QUrl(url), std::shared_ptr<PhotoSize>(new PhotoSizeBrowser(size, suffix)));

        // 3. FullScreen size
        suffix = mDefaultPhotoSize.fullscreen.getSuffix();
        size = mDefaultPhotoSize.fullscreen.getSize();
        url = QString("%1/%2%3.%4")
                .arg(fileInfo.path())
                .arg(fileInfo.baseName()
                     .left(leftLen))
                .arg(suffix)
                .arg(fileInfo.suffix());
        mUrlHash.insert(QUrl(url), std::shared_ptr<PhotoSize>(new PhotoSizeFullScreen(size, suffix)));
    }
}

QHashIterator<QUrl, std::shared_ptr<PhotoSize>> UrlTransformerPublic::createIterator()
{
    QHashIterator<QUrl, std::shared_ptr<PhotoSize>> iter(mUrlHash);
    return iter;
}
