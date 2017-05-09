#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <memory>

class DatabaseManager
{
public:
    DatabaseManager();
    DatabaseManager(DatabaseManager&&) {}
    DatabaseManager(const DatabaseManager&) {}
    DatabaseManager& operator=(const DatabaseManager&) {}
    DatabaseManager& operator=(DatabaseManager&&) {}
    ~DatabaseManager();

    std::shared_ptr<QSqlDatabase> getDatabase() const;
    QString getTableName() const;

private:
    void createConnection();
    void createTable();

private:
    QSqlDatabase mDatabase;
    QString mFilename;
    QString mCurrentPath;
    const QString mDatabaseDriverName = QStringLiteral("QSQLITE");
    const QString mPhotosDB = QStringLiteral("/photos-database.sqlite3");
    const QString mTableName = QStringLiteral("Flickstr");

};

#endif
