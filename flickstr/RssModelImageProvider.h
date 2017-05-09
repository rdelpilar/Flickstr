#ifndef RSSMODELIMAGEPROVIDER_H
#define RSSMODELIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include "RssListModel.h"

class RssModelImageProvider : public QQuickImageProvider
{
public:
    RssModelImageProvider(std::shared_ptr<RssListModel>);
    ~RssModelImageProvider();
    QPixmap requestPixmap(const QString&, QSize*, const QSize&);

private:
    std::shared_ptr<RssListModel> mListModel;
    int mIndex;
};

#endif
