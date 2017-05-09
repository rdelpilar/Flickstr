#include "flickstr/RssModelImageProvider.h"

#include <QDebug>

RssModelImageProvider::RssModelImageProvider(std::shared_ptr<RssListModel> listModel)
    : QQuickImageProvider(QQuickImageProvider::Pixmap),
      mListModel(listModel),
      mIndex(0)
{
}

RssModelImageProvider::~RssModelImageProvider()
{
}

// id format : rssListModelIndex/rssIndex/date including milliseconds
// eg: 0/1/Quality/09:37.55, 0/2/Quality/09:38.32, 0/3/Quality/09:45.12, 0/4/Quality/09:55.01, ...
QPixmap RssModelImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    auto list = id.split('/');
    int outerModelIndex = list.at(0).toInt();
    if(outerModelIndex < 0 || outerModelIndex > mListModel->rowCount())
        return QPixmap();

    QModelIndex index = mListModel->index(outerModelIndex, 0);
    RssModel *rssModel = mListModel->data(index, mListModel->RssModelRole).value<RssModel*>();

    int innerModelIndex = list.at(1).toInt();
    if(innerModelIndex < 0 || innerModelIndex > rssModel->rowCount())
        return QPixmap();

    QModelIndex rssIndex = rssModel->index(innerModelIndex, 0);

    QString quality(list.at(2));

    QPixmap image;
    image.loadFromData(*rssModel->data(rssIndex, rssModel->PhotoDataRole)
                        .value<QByteArray*>());
    QPixmap result;

    if(requestedSize.isValid() && quality == "Thumbnail") {
        //result = image.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        result = image;
    } else if(requestedSize.isValid() && quality == "HighQuality"){
        //result = image;
        // Lazy download implementation:
        // Only download when requested
        auto url = rssModel->data(rssIndex, rssModel->UrlRole);
        qDebug() << url;
    }

    *size = result.size();

    return result;
}
