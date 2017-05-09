#include <memory>
#include "flickstr/UrlTransform.h"
#include "flickstr/UrlTransformPublic.h"

UrlTransform::UrlTransform(const QStringListIterator &iterator,
                           const DefaultPhotoSize &photoSize,
                           const RequestType &requestType)
    : mIterator(iterator),
      mPhotoSize(photoSize),
      mRequestType(requestType)
{
}

QHashIterator<QUrl, std::shared_ptr<PhotoSize>> UrlTransform::transform()
{

    std::unique_ptr<UrlTransformInterface> IUrlTransform = nullptr;

    switch(mRequestType) {
    case RequestType::PUBLIC_SEARCH :
    {
        IUrlTransform = std::unique_ptr<UrlTransformInterface>(new UrlTransformPublic(mIterator, mPhotoSize));
        IUrlTransform->transform();
        break;
    }
    default:
        break;
    }

    return IUrlTransform->createIterator();
}
