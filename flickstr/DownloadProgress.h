#ifndef DOWNLOADPROGRESS_H
#define DOWNLOADPROGRESS_H

#include <QObject>

class DownloadProgress
{
public:
    DownloadProgress();
    DownloadProgress(DownloadProgress&&) noexcept;
    DownloadProgress(const DownloadProgress&) noexcept;
    DownloadProgress& operator=(const DownloadProgress&) noexcept;
    DownloadProgress& operator=(DownloadProgress&&) noexcept;
    ~DownloadProgress() noexcept;

    bool visible() const;
    void setVisible(bool);

    void setValue(qreal);
    qreal getValue() const;

private:
    bool mVisible;
    qreal mValue;
};

#endif
