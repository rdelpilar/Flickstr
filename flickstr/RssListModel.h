#ifndef RSSLISTMODEL_H
#define RSSLISTMODEL_H

#include <QAbstractListModel>
#include "flickstr/RssModel.h"

class RssListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ListRoles { RssModelRole = Qt::UserRole + 1 };

    RssListModel(QObject *parent = 0);
    RssListModel(RssListModel&&) noexcept;
    RssListModel(const RssListModel&) noexcept;
    RssListModel& operator=(const RssListModel&) noexcept;
    RssListModel& operator=(RssListModel&&) noexcept;
    ~RssListModel() noexcept;

    void createDummyListModel();
    void removeRssModel(const int);
    void resetRssModel(const int);

    void setRssModelTag(const int, QString&);
    bool rssModelTagEmpty(const int) const;
    int getRssModelSize(const int) const;

    void addRss(const int, const Rss&);

    int rowCount(const QModelIndex& = QModelIndex()) const;
    QVariant data(const QModelIndex&, int) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<std::shared_ptr<RssModel>> mModelList;
};

#endif
