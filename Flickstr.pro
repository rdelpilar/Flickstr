TEMPLATE = app

QT += core qml quick widgets xml xmlpatterns sql

CONFIG += c++11

!contains(sql-drivers, sqlite): QTPLUGIN += qsqlite

RESOURCES += flickstr.qrc

lupdate_only {
SOURCES = CoreQml/*.qml
}

HEADERS += \
    flickstr/ApiKeyManager.h \
    flickstr/Controller.h \
    flickstr/HttpRequestFactory.h \
    flickstr/HttpRequest.h \
    flickstr/FileManager.h \
    flickstr/PhotoSize.h \
    flickstr/UrlTransformerPublic.h \
    flickstr/UrlTransformerHandler.h \
    flickstr/XmlParserPublic.h \
    flickstr/XmlParserHandler.h \
    flickstr/PhotoDownloader.h \
    flickstr/XmlDownloader.h \
    flickstr/DownloadHandler.h \
    flickstr/UrlTransformerPrivate.h \
    flickstr/XmlParserPrivate.h \
    flickstr/DatabaseManager.h \
    flickstr/TagSqlModel.h \
    flickstr/RssModel.h \
    flickstr/Rss.h \
    flickstr/SearchParametersHandler.h \
    flickstr/SearchParameters.h \
    flickstr/UrlBuilder.h \
    flickstr/UrlBuilderPrivate.h \
    flickstr/UrlBuilderPublic.h \
    flickstr/DownloadProgressHandler.h \
    flickstr/DownloadProgress.h \
    flickstr/RssModelImageProvider.h \
    flickstr/RssListModel.h

SOURCES += src/main.cpp \
    src/ApiKeyManager.cpp \
    src/Controller.cpp \
    src/FileManager.cpp \
    src/UrlTransformerPublic.cpp \
    src/UrlTransformerHandler.cpp \
    src/XmlParserPublic.cpp \
    src/XmlParserHandler.cpp \
    src/PhotoDownloader.cpp \
    src/HttpRequest.cpp \
    src/XmlDownloader.cpp \
    src/DownloadHandler.cpp \
    src/UrlTransformerPrivate.cpp \
    src/XmlParserPrivate.cpp \
    src/DatabaseManager.cpp \
    src/TagSqlModel.cpp \
    src/RssModel.cpp \
    src/Rss.cpp \
    src/SearchParametersHandler.cpp \
    src/SearchParameters.cpp \
    src/UrlBuilder.cpp \
    src/UrlBuilderPrivate.cpp \
    src/UrlBuilderPublic.cpp \
    src/DownloadProgressHandler.cpp \
    src/DownloadProgress.cpp \
    src/RssModelImageProvider.cpp \
    src/RssListModel.cpp

include(deployment.pri)
