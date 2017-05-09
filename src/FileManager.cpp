#include "flickstr/FileManager.h"
#include <QFile>

FileManager::FileManager()
    : mCurrentPath(QDir::currentPath())
{
}

void FileManager::save(const QHash<QString, Rss>::iterator &hashIter)
{
    auto hashKey(hashIter.key());
    if(hashKey.isEmpty())
        return;

    QString absFilePath(createAbsoluteFilePath(hashIter));
    saveToDisk(absFilePath, hashIter);
}

void FileManager::save(const std::shared_ptr<QMutableHashIterator<QString, Rss>> &hashIter)
{
    if(mCurrentPath.isNull() || mCurrentPath.isEmpty())
        mCurrentPath = QDir::currentPath();

    while(hashIter->hasNext()) {
        QHash<QString, Rss>::iterator it = hashIter->next();

        QString absFilePath(createAbsoluteFilePath(it));
        createDirPath(absFilePath);

        bool ret = saveToDisk(absFilePath, it);
        if(true == ret)
            saveFileAbsolutePath(it, absFilePath);
    }
}

QString FileManager::createAbsoluteFilePath(const QHash<QString, Rss>::const_iterator &hashIter)
{
    auto fileName = ::UrlToFilePath(hashIter.value().getUrl());
    auto tagLabel = hashIter.key();

    auto absoluteFilePath = QString("%1/%2/%3/%4")
            .arg(mCurrentPath)
            .arg(kDownloadRoot)
            .arg(tagLabel)
            .arg(fileName);
    return absoluteFilePath;
}

void FileManager::createDirPath(const QString &absoluteFilePath)
{
    QFileInfo fileInfo(absoluteFilePath);
    auto path = fileInfo.absolutePath();

    mDir.setPath(path);
    if(!mDir.exists())
        mDir.mkpath(path);
}

bool FileManager::saveToDisk(const QString &absPath, const QHash<QString, Rss>::iterator &hashIter)
{
    QFile file(absPath);
    if(file.exists())
        return false;

    if(!file.open(QIODevice::WriteOnly))
        return false;

    auto byteArray = *hashIter->getData();

    file.write(byteArray);
    file.close();

    return true;
}

void FileManager::saveFileAbsolutePath(const QHash<QString, Rss>::iterator &hashIter, const QString& filePath)
{
    auto path(filePath);
    hashIter.value().setAbsolutePath(path);
}
