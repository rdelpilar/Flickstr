#include "flickstr/UrlTransformerHandler.h"
#include "flickstr/UrlTransformerPublic.h"
#include "flickstr/UrlTransformerPrivate.h"

UrlTransformerHandler::UrlTransformerHandler(const std::shared_ptr<QStringListIterator> &iterator,
                                             const PhotoSize::Size &photoSize,
                                             const RequestType &requestType)
    : mInputListIterator(iterator),
      mPhotoSize(photoSize),
      mRequestType(requestType),
      mSize(0)
{
}

std::shared_ptr<QListIterator<QUrl>> UrlTransformerHandler::transform()
{
    if(RequestType::PUBLIC_SEARCH == mRequestType) {
        UrlTransformerPublic urlTransformer(mInputListIterator, mPhotoSize);
        transform(urlTransformer);
        setSize(urlTransformer);
        return urlTransformer.createIterator();
    } else if(RequestType::PRIVATE_SEARCH == mRequestType) {
        UrlTransformerPrivate urlTransformer(mInputListIterator, mPhotoSize);
        transform(urlTransformer);
        setSize(urlTransformer);
        return urlTransformer.createIterator();
    }

    return nullptr;
}

size_t UrlTransformerHandler::size() const
{
    return mSize;
}

template <typename T>
void UrlTransformerHandler::transform(T &transformer)
{
    transformer.transform();
}

template <typename T>
void UrlTransformerHandler::setSize(T &transformer)
{
    mSize = transformer.size();
}
