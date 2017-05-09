#ifndef TAGSQLMODEL_H
#define TAGSQLMODEL_H

#include <QSqlTableModel>
#include "Rss.h"

class TagSqlModel : public QSqlTableModel
{
public:
    TagSqlModel(QObject *parent = 0, const QString& = "");
    TagSqlModel(TagSqlModel&&) {}
    TagSqlModel(const TagSqlModel&) {}
    TagSqlModel& operator=(const TagSqlModel&) {}
    TagSqlModel& operator=(TagSqlModel&&) {}
    ~TagSqlModel() = default;

    void addRss(const QString&, const Rss&);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

private:
    QString mTableName;
};

#endif
