#ifndef APIKEYMANAGER_H
#define APIKEYMANAGER_H

#include <QFile>
#include <QString>

/* Handles the Flickr Api Key
 * Get your key here: https://www.flickr.com/services/apps/create/apply
 */

class ApiKeyManager
{
public:
    typedef const enum QIODevice::OpenModeFlag FileOpenMode;

    ApiKeyManager();
    ApiKeyManager(ApiKeyManager&&) = default;
    ApiKeyManager(const ApiKeyManager&) = delete;
    ApiKeyManager& operator=(const ApiKeyManager&) = delete;
    ApiKeyManager& operator=(ApiKeyManager&&) = default;
    ~ApiKeyManager() noexcept = default;

    QString getKey() const;
    void setKey(const QString&);

private:
    void readKeyFromFile();
    void writeKeyToFile();
    void fileOperationHelper(FileOpenMode&);

private:
    QString mKey;
    const QString mKeyFilename = QStringLiteral("FlickrApiKey.txt");
};

#endif
