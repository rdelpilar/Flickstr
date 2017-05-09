#include "flickstr/UrlTransformerPublic.h"
#include <QFileInfo>

UrlTransformerPublic::UrlTransformerPublic(const std::shared_ptr<QStringListIterator> &iterator,
                                           const PhotoSize::Size &photoSize)
    : mInputListIterator(iterator),
      mPhotoSize(photoSize)
{
}

void UrlTransformerPublic::transform()
{
    QString url;

    while(mInputListIterator->hasNext()) {
        QFileInfo fileInfo(mInputListIterator->next());

        if(fileInfo.suffix().compare(QStringLiteral("jpg"), Qt::CaseInsensitive) != 0)
            continue;

        auto sizeLabel = ::enumToSizeSuffix(mPhotoSize);

        // Remove the size label from file name
        auto leftLen = fileInfo.baseName().size() - sizeLabel.size();
        if(leftLen <= 0) continue;

        url = QString("%1/%2%3.%4")
                .arg(fileInfo.path())
                .arg(fileInfo.baseName().left(leftLen))
                .arg(sizeLabel)
                .arg(fileInfo.suffix());

        mUrlList.push_back(QUrl::fromEncoded(url.toLocal8Bit()));
    }
}

std::shared_ptr<QListIterator<QUrl>> UrlTransformerPublic::createIterator()
{
    return std::make_shared<QListIterator<QUrl>>(mUrlList);
}

size_t UrlTransformerPublic::size() const
{
    return mUrlList.count();
}
