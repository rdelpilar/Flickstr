#ifndef DOWNLOADPROGRESSHANDLER_H
#define DOWNLOADPROGRESSHANDLER_H

#include <QObject>
#include <QVariant>
#include <QHash>
#include <memory>
#include "DownloadProgress.h"

class DownloadProgressHandler : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(bool currentVisible NOTIFY currentVisibleChanged)

public:
    DownloadProgressHandler(QObject *parent = 0);
    DownloadProgressHandler(int, size_t);
    DownloadProgressHandler(DownloadProgressHandler&&) noexcept;
    DownloadProgressHandler(const DownloadProgressHandler&) noexcept;
    DownloadProgressHandler& operator=(const DownloadProgressHandler&) noexcept;
    DownloadProgressHandler& operator=(DownloadProgressHandler&&) noexcept;
    ~DownloadProgressHandler() noexcept;

    void createDownloadProgress(int);

    Q_INVOKABLE bool getVisibleState(int);
    Q_INVOKABLE qreal getValue(int);

    void setVisible(int, bool);
    void setValue(int, qreal);
    void removeDownloadProgress(int);

signals:
    void visibleChanged();
    void valueChanged();

private:
    QHash<int, std::shared_ptr<DownloadProgress>> mDownloadProgressCont;
};

#endif
