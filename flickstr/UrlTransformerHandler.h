#ifndef URLTRANSFORMERHANDLER_H
#define URLTRANSFORMERHANDLER_H

#include "SearchParameters.h"
#include "HttpRequest.h"
#include "PhotoSize.h"

class UrlTransformerHandler
{
public:
    UrlTransformerHandler() = default;
    UrlTransformerHandler(const std::shared_ptr<QStringListIterator>&,
                          const PhotoSize::Size&,
                          const RequestType&);
    UrlTransformerHandler(UrlTransformerHandler&&) = delete;
    UrlTransformerHandler(const UrlTransformerHandler&) = delete;
    UrlTransformerHandler& operator=(const UrlTransformerHandler&) = delete;
    UrlTransformerHandler& operator=(const UrlTransformerHandler&&) = delete;
    ~UrlTransformerHandler() = default;

    std::shared_ptr<QListIterator<QUrl>> transform();
    size_t size() const;

private:
    template <typename T>
    void transform(T&);

    template <typename T>
    void setSize(T&);

private:
    std::shared_ptr<QStringListIterator> mInputListIterator;
    PhotoSize::Size mPhotoSize;
    RequestType mRequestType;
    size_t mSize;
};

#endif
