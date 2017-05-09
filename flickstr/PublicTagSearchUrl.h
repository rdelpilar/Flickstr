#ifndef PUBLICTAGSEARCHURL_H
#define PUBLICTAGSEARCHURL_H

#include <QHashIterator>
#include "flickstr/InterfaceUrlBuilder.h"

class PublicTagSearchUrl : public InterfaceUrlBuilder
{
public:
    PublicTagSearchUrl(const QHashIterator<QString, QString>&);
    virtual QUrl getUrl();

private:
    QHashIterator<QString, QString> mIterator;
    const QString API_URL = "https://api.flickr.com/services/feeds/photos_public.gne?";
};

#endif
