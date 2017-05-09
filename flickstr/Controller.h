#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickItem>
#include <QJSEngine>
#include <QUrl>
#include <QHash>
#include <QList>

#include "ApiKeyManager.h"
#include "SearchParameters.h"
#include "HttpRequest.h"
#include "Rss.h"
#include "PhotoSize.h"
#include "DownloadHandler.h"
#include "XmlDownloader.h"
#include "RssModelImageProvider.h"
#include "DownloadProgressHandler.h"
#include "PhotoDownloader.h"
#include "RssListModel.h"
#include "RssModel.h"

//#include "DatabaseManager.h"
//#include "FileManager.h"
//#include "TagSqlModel.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Controller)

public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    static QObject* provider(QQmlEngine *engine = NULL,
                             QJSEngine *scriptEngine = NULL);

    void init(QQmlApplicationEngine *);

    // FlickrApiKey
    Q_INVOKABLE void setApiKey(QString);
    Q_INVOKABLE QString getApiKey() const;

    // SearchQuery
    Q_INVOKABLE void createDummyListModel();
    Q_INVOKABLE void setTag(int, QString);
    Q_INVOKABLE void setContentType(QString);
    Q_INVOKABLE void setPerPage(QString);
    Q_INVOKABLE void setPage(QString);

    Q_INVOKABLE void setPhotoSize(QString);
    PhotoSize::Size getPhotoSize() const;

private:
    void execRequest(const QString&, const int index);
    SearchParameters buildParameters(const QString &);
    QUrl buildUrl(const SearchParameters&);
    void xmlDownloadStart(const SearchParameters&, const QUrl&, const int);
    std::shared_ptr<QStringListIterator> parseXml(const SearchParameters&, const QByteArray&);
    void initDownloadProgress(const int);
    void photoDownloadStart(const SearchParameters&, const std::shared_ptr<QListIterator<QUrl>>&, const size_t, const int);
    void updateDownloadProgress(const int, const size_t);
    void updateDownloadProgressFinished(const int);
    void setPhotoRect(Rss&);

public slots:
    void photoDownloadFinished(const QString&, const QUrl&, const QByteArray&, const size_t, const int);
    void xmlDownloadFinished(const SearchParameters&, const QByteArray&, const int);

private:
    QQmlApplicationEngine *mEngine;
    ApiKeyManager mKeyManager;
    QHash<int, std::shared_ptr<DownloadHandler>> mDownloaderCont;
    std::shared_ptr<RssListModel> mListModel;
    DownloadProgressHandler mDownloadProgressHandler;
    SearchParameters::Builder mParamsBuilder;
    PhotoSize::Size mPhotoSize;


    //DatabaseManager mDbManager;
    //FileManager mFileManager;
    //TagSqlModel mSqlModel;
};

#endif
