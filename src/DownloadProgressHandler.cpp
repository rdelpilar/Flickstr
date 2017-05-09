#include "flickstr/DownloadProgressHandler.h"
#include <QDebug>

DownloadProgressHandler::DownloadProgressHandler(QObject *parent)
    : QObject(parent),
      mDownloadProgressCont(QHash<int, std::shared_ptr<DownloadProgress>>())
{

}

DownloadProgressHandler::DownloadProgressHandler(DownloadProgressHandler &&rhs) noexcept
    : QObject(nullptr),
      mDownloadProgressCont(rhs.mDownloadProgressCont)
{

}

DownloadProgressHandler::DownloadProgressHandler(const DownloadProgressHandler &rhs) noexcept
    : QObject(nullptr),
      mDownloadProgressCont(rhs.mDownloadProgressCont)
{

}

DownloadProgressHandler& DownloadProgressHandler::operator=(const DownloadProgressHandler &rhs) noexcept
{
    if(this == &rhs)
        return *this;
    DownloadProgressHandler tmp(rhs);
    *this = std::move(tmp);
    return *this;
}

DownloadProgressHandler& DownloadProgressHandler::operator=(DownloadProgressHandler &&rhs) noexcept
{
    mDownloadProgressCont = rhs.mDownloadProgressCont;
    return *this;
}

DownloadProgressHandler::~DownloadProgressHandler()
{

}

void DownloadProgressHandler::createDownloadProgress(int index)
{
    if(index < 0) return;

    if(mDownloadProgressCont.contains(index))
        mDownloadProgressCont.remove(index);

    mDownloadProgressCont.insert(index, std::make_shared<DownloadProgress>());
}

bool DownloadProgressHandler::getVisibleState(int index)
{
    if(index < 0 || !mDownloadProgressCont.contains(index)) return false;

    return mDownloadProgressCont.value(index)->visible();
}

qreal DownloadProgressHandler::getValue(int index)
{
    if(index < 0 || !mDownloadProgressCont.contains(index)) return false;

    return mDownloadProgressCont.value(index)->getValue();
}

void DownloadProgressHandler::setVisible(int index, bool visible)
{
    if(index < 0 || !mDownloadProgressCont.contains(index)) return;

    mDownloadProgressCont.value(index)->setVisible(visible);
    emit visibleChanged();
}

void DownloadProgressHandler::setValue(int index, qreal value)
{
    if(index < 0 || !mDownloadProgressCont.contains(index)) return;

    mDownloadProgressCont.value(index)->setValue(value);
    emit valueChanged();
}

void DownloadProgressHandler::removeDownloadProgress(int index)
{
    if(index < 0 || !mDownloadProgressCont.contains(index)) return;

    mDownloadProgressCont.remove(index);
}
