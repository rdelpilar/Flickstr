#ifndef URLTRANSFORMINTERFACE_H
#define URLTRANSFORMINTERFACE_H

#include <QHash>
#include <QUrl>
#include <memory>
#include "PhotoSize.h"

class UrlTransformInterface
{
public:
    UrlTransformInterface() = default;
    UrlTransformInterface(UrlTransformInterface&&) = delete;
    UrlTransformInterface(const UrlTransformInterface&) = delete;
    UrlTransformInterface& operator=(const UrlTransformInterface&) = delete;
    UrlTransformInterface& operator=(const UrlTransformInterface&&) = delete;
    virtual ~UrlTransformInterface() = default;

    virtual void transform() = 0;
    virtual QHashIterator<QUrl, std::shared_ptr<PhotoSize>> createIterator() = 0;
};

#endif
