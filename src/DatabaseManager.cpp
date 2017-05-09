#include "flickstr/DatabaseManager.h"
#include <QSqlQuery>
#include <QDir>

DatabaseManager::DatabaseManager()
    : mFilename(QStringLiteral("")),
      mCurrentPath(QDir::currentPath())
{
    createConnection();
    createTable();
}

DatabaseManager::~DatabaseManager()
{
    mDatabase.close();
}

std::shared_ptr<QSqlDatabase> DatabaseManager::getDatabase() const
{
    return std::make_shared<QSqlDatabase>(mDatabase);
}

QString DatabaseManager::getTableName() const
{
    return mTableName;
}

void DatabaseManager::createConnection()
{
    mDatabase = QSqlDatabase::database();
    if(!mDatabase.isValid()) {
        mDatabase = QSqlDatabase::addDatabase(mDatabaseDriverName);
        if(!mDatabase.isValid()) {
            return;
        }
    }

    mFilename = QString("%1%2")
            .arg(mCurrentPath)
            .arg(mPhotosDB);

    mDatabase.setDatabaseName(mFilename);

    if(!mDatabase.open())
        QFile::remove(mFilename);
}

void DatabaseManager::createTable()
{
    if(QSqlDatabase::database().tables().contains(mTableName))
        return;

    /*
     * id: generated by sqlite during insertion (INTEGER)
     * tag: the tag associated with this photo (TEXT)
     * url: the flickr url of this photo (TEXT)
     * sizelabel: size of photo from PhotoSize.h. This is used internally (TEXT)
     * photowidth: width of photo calculated by QPixmap (INTEGER)
     * photoheight: height of photo calculated by QPixmap (INTEGER)
     * photoblob: data of photo (BLOB)
     * photoroix: region of interest x position (INTEGER)
     * photoroiy: region of interest y position (INTEGER)
     * photoroiwidth: region of interest width (INTEGER)
     * photoroiheight: region of interest height (INTEGER)
     */

    QSqlQuery query;
    if(!query.exec(
                "CREATE TABLE IF NOT EXISTS 'Flickstr' ("
                "'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                "'tag' TEXT NOT NULL,"
                "'filename' TEXT NOT NULL,"
                "'sizelabel' TEXT NOT NULL,"
                "'photowidth' INTEGER NOT NULL,"
                "'photoheight' INTEGER NOT NULL,"
                "'photoblob' BLOB NOT NULL,"
                "'photoroix' INTEGER NOT NULL,"
                "'photoroiy' INTEGER NOT NULL,"
                "'photoroiwidth' INTEGER NOT NULL,"
                "'photoroiheight' INTEGER NOT NULL"
                ")")) {
        ; // SET Global error
    }
}
