#include "flickstr/TagSqlModel.h"
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlField>

TagSqlModel::TagSqlModel(QObject *parent, const QString &tableName)
    : QSqlTableModel(parent),
      mTableName(tableName)
{
    setTable(mTableName);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void TagSqlModel::addRss(const QString& tag, const Rss &rss)
{
    auto tagItem = tag;
    auto rssItem(rss);
    auto filename = rssItem.getFilename().toUtf8();
    auto width = rssItem.getPhotoRect().width();
    auto height = rssItem.getPhotoRect().height();
    auto data = *rssItem.getData();


    // NEXT IS TO FIGURE OUT WHAT TO DO WITH THE ALBUM AND BROWSER sizes
    // width: 140; height: 133
    QSqlRecord newRecord = record();
    newRecord.setGenerated(Qt::UserRole, true);
    newRecord.setValue("tag", tagItem);
    newRecord.setValue("filename", filename);
    newRecord.setValue("photowidth", width);
    newRecord.setValue("photoheight", height);
    newRecord.setValue("photoblob", data);

    // values for the following fields will be dynamically set
    newRecord.setValue("photoroix", 0); //intetger
    newRecord.setValue("photoroiy", 0); //integer
    newRecord.setValue("photoroiwidth", 0); //integer
    newRecord.setValue("photoroiheight", 0); // integer

    auto row = rowCount();
    if(!insertRecord(row, newRecord))
        return;

    submitAll();
}

QVariant TagSqlModel::data(const QModelIndex &index, int role) const
{
//    if(!index.isValid())
//        return QVariant();

//    if(index.row() >= rowCount() || index.row() < 0)
//        return QVariant();

    if (role < Qt::UserRole)
        return QSqlTableModel::data(index, role);

    const QSqlRecord sqlRecord = record(index.row());
    auto ret = sqlRecord.value(role - Qt::UserRole);
    qDebug() << ret.toString();
    return ret;
}

QHash<int, QByteArray> TagSqlModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Qt::UserRole] = "id";
    names[Qt::UserRole + 1] = "tag";
    names[Qt::UserRole + 2] = "filename";
    names[Qt::UserRole + 3] = "sizelabel";
    names[Qt::UserRole + 4] = "photowidth";
    names[Qt::UserRole + 5] = "photoheight";
    names[Qt::UserRole + 6] = "photoblob";
    names[Qt::UserRole + 7] = "photoroix";
    names[Qt::UserRole + 8] = "photoroiy";
    names[Qt::UserRole + 9] = "photoroiwidth";
    names[Qt::UserRole + 10] = "photoroiheight";
    return names;
}
