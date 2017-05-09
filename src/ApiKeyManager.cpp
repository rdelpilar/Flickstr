#include <QTextStream>
#include "flickstr/ApiKeyManager.h"

ApiKeyManager::ApiKeyManager()
    : mKey("")
{
    readKeyFromFile();
}

QString ApiKeyManager::getKey() const
{
    return mKey;
}

void ApiKeyManager::setKey(const QString &key)
{
    if(!key.isNull() && key != mKey) {
        mKey = key;
        writeKeyToFile();
    }
}

void ApiKeyManager::readKeyFromFile()
{
    fileOperationHelper(QIODevice::ReadOnly);
}

void ApiKeyManager::writeKeyToFile()
{
    fileOperationHelper(QIODevice::WriteOnly);
}

void ApiKeyManager::fileOperationHelper(FileOpenMode &flag)
{
    QFile file(mKeyFilename);
    if(!file.open(flag | QIODevice::Text))
        return;

    QTextStream textStream(&file);
    if(textStream.status() != QTextStream::Ok) return;

    switch(flag) {
    case QIODevice::ReadOnly: { mKey = textStream.readLine(); break;}
    case QIODevice::WriteOnly: { textStream << mKey; break; }
    default: break;
    }
    file.close();
}
