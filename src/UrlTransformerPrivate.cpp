#include "flickstr/UrlTransformerPrivate.h"

UrlTransformerPrivate::UrlTransformerPrivate(const std::shared_ptr<QStringListIterator> &iterator,
                                             const PhotoSize::Size &photoSize)
    : mInputListIterator(iterator),
      mPhotoSize(photoSize)
{
}

#include <QDebug>
void UrlTransformerPrivate::transform()
{
    // Input from string list iterator
    // Each item has comma delimited strings
    // 31970906646,a91038624d,317,1
    // where:
    // photo-id,secret,server-id,farm-id

    // Example
    // https://farm1.staticflickr.com/2/1418878_1e92283336_m.jpg
    // farm-id: 1
    // server-id: 2
    // photo-id: 1418878
    // secret: 1e92283336
    // size: m

    QString url;
    QVector<QStringRef> tokens;
    const QString urlPrefix("https://farm");
    const QString domain(".staticflickr.com/");
    const QString suffix(".jpg");

    while(mInputListIterator->hasNext()) {
        QStringRef ref(&mInputListIterator->next());
        tokens = ref.split(':');
        url = QString("%1%2%3%4/%5_%6%7%8")
                .arg(urlPrefix)
                .arg(tokens.at(ATTRIBUTE::FARMID).toString())
                .arg(domain)
                .arg(tokens.at(ATTRIBUTE::SERVERID).toString())
                .arg(tokens.at(ATTRIBUTE::PHOTOID).toString())
                .arg(tokens.at(ATTRIBUTE::SECRET).toString())
                .arg(::enumToSizeSuffix(mPhotoSize))
                .arg(suffix);

        mUrlList.push_back(QUrl::fromEncoded(url.toLocal8Bit()));
    }
}

std::shared_ptr<QListIterator<QUrl>> UrlTransformerPrivate::createIterator()
{
    return std::make_shared<QListIterator<QUrl>>(mUrlList);
}

size_t UrlTransformerPrivate::size() const
{
    return mUrlList.count();
}
