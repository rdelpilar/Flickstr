#include "flickstr/DownloadProgress.h"

#include <memory>

DownloadProgress::DownloadProgress()
    : mVisible(false),
      mValue(0)
{
}

DownloadProgress::DownloadProgress(DownloadProgress &&rhs) noexcept
    : mVisible(rhs.mVisible),
      mValue(rhs.mValue)
{

}

DownloadProgress::DownloadProgress(const DownloadProgress &rhs) noexcept
    : mVisible(rhs.mVisible),
      mValue(rhs.mValue)
{

}

DownloadProgress& DownloadProgress::operator=(const DownloadProgress &rhs) noexcept
{
    if(this == &rhs)
        return *this;
    DownloadProgress tmp(rhs);
    *this = std::move(tmp);
    return *this;
}

DownloadProgress& DownloadProgress::operator=(DownloadProgress &&rhs) noexcept
{
    mVisible = rhs.mVisible;
    mValue = rhs.mValue;
    return *this;
}

DownloadProgress::~DownloadProgress()
{

}

bool DownloadProgress::visible() const
{
    return mVisible;
}

void DownloadProgress::setVisible(bool visible)
{
    if(mVisible != visible)
        mVisible = visible;
}

void DownloadProgress::setValue(qreal value)
{
    if(mValue != value)
        mValue = value;
}

qreal DownloadProgress::getValue() const
{
    return mValue;
}
