#ifndef URLTRANSFORMERPRIVATE_H
#define URLTRANSFORMERPRIVATE_H

#include <QUrl>
#include <memory>
#include "PhotoSize.h"

class UrlTransformerPrivate
{
public:
    enum ATTRIBUTE { PHOTOID = 0, SECRET = 1, SERVERID = 2, FARMID = 3 };
    UrlTransformerPrivate() = default;
    UrlTransformerPrivate(const std::shared_ptr<QStringListIterator>&, const PhotoSize::Size&);
    UrlTransformerPrivate(UrlTransformerPrivate&&) = delete;
    UrlTransformerPrivate(const UrlTransformerPrivate&) = delete;
    UrlTransformerPrivate& operator=(const UrlTransformerPrivate&) = delete;
    UrlTransformerPrivate& operator=(const UrlTransformerPrivate&&) = delete;
    ~UrlTransformerPrivate() {}

    void transform();
    std::shared_ptr<QListIterator<QUrl>> createIterator();
    size_t size() const;

private:
    std::shared_ptr<QStringListIterator> mInputListIterator;
    PhotoSize::Size mPhotoSize;
    QList<QUrl> mUrlList;
};

#endif
