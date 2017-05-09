#ifndef URLTRANSFORMERPUBLIC_H
#define URLTRANSFORMERPUBLIC_H

#include <QUrl>
#include <memory>
#include "PhotoSize.h"

class UrlTransformerPublic
{
public:    
    UrlTransformerPublic() = default;
    UrlTransformerPublic(const std::shared_ptr<QStringListIterator>&, const PhotoSize::Size&);
    UrlTransformerPublic(UrlTransformerPublic&&) = delete;
    UrlTransformerPublic(const UrlTransformerPublic&) = delete;
    UrlTransformerPublic& operator=(const UrlTransformerPublic&) = delete;
    UrlTransformerPublic& operator=(const UrlTransformerPublic&&) = delete;
    ~UrlTransformerPublic() {}

    void transform();
    std::shared_ptr<QListIterator<QUrl>> createIterator();
    size_t size() const;

private:
    std::shared_ptr<QStringListIterator> mInputListIterator;
    PhotoSize::Size mPhotoSize;
    QList<QUrl> mUrlList;
};

#endif
