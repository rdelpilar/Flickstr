#ifndef RSSMODEL_H
#define RSSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "Rss.h"

class RssModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum RssModelRoles {
        TagLabelRole = Qt::UserRole + 1,
        UrlRole,
        FilenameRole,
        PhotoWidthRole,
        PhotoHeightRole,
        PhotoDataRole,
        PhotoThumbnailRole,
        PhotoHighQualityRole,
        PhotoRoiXRole,
        PhotoRoiYRole,
        PhotoRoiWidthRole,
        PhotoRoiHeightRole
    };

    RssModel(QObject *parent = 0);
    RssModel(const QString& , QObject *parent = 0);
    RssModel(RssModel&&) noexcept;
    RssModel(const RssModel&) noexcept;
    RssModel& operator=(const RssModel&) noexcept;
    RssModel& operator=(RssModel&&) noexcept;
    ~RssModel() noexcept;

    void addRss(const Rss&);
    int getSize() const;

    void setParentIndex(const int);

    RssModelRoles getPhotoDataRole() const;
    int rowCount(const QModelIndex& = QModelIndex()) const;

    //bool insertRows(int row, int count, const QModelIndex &parent); // TODO
    //bool removeRows(int row, int count, const QModelIndex &parent); // TODO
    //bool canFetchMore(const QModelIndex &parent) const; // TODO
    //void fetchMore(const QModelIndex &parent); // TODO
    //Qt::ItemFlags flags(const QModelIndex &index) const; //TODO

    QVariant data(const QModelIndex&, int) const;
    void resetRssModel();
    //bool setData(const QModelIndex &index, const QVariant &value, int role); // TODO

    //QList<Rss> rssModelList() const;

    QString tag() const;
    void setTag(const QString&);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    int mParentIndex;
    QString mTag;
    QList<Rss> mRssModelList;
};

Q_DECLARE_METATYPE(const RssModel*)
Q_DECLARE_METATYPE(QByteArray*)

#endif

