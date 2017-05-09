#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QHash>
#include <QDir>
#include "PhotoSize.h"
#include "Rss.h"

class FileManager
{
public:
    FileManager();
//    FileManager(FileManager&&) = default;
//    FileManager(const FileManager&) = default;
//    FileManager& operator=(const FileManager&) = default;
//    FileManager& operator=(FileManager&&) = default;
    ~FileManager() = default;

    void save(const QHash<QString, Rss>::iterator&);
    void save(const std::shared_ptr<QMutableHashIterator<QString, Rss>>&);

private:
    QString createAbsoluteFilePath(const QHash<QString, Rss>::const_iterator&);
    void createDirPath(const QString&);
    bool saveToDisk(const QString&, const QHash<QString, Rss>::iterator&);
    void saveFileAbsolutePath(const QHash<QString, Rss>::iterator &hashIter, const QString&);

private:
    QString mCurrentPath;
    QDir mDir;
    const QString kDownloadRoot = QStringLiteral("Downloads");
};

#endif
