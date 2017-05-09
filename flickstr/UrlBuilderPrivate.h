#ifndef URLBUILDERPRIVATE_H
#define URLBUILDERPRIVATE_H

#include <QUrl>
#include "SearchParameters.h"

class UrlBuilderPrivate
{
public:
    UrlBuilderPrivate() = default;
    UrlBuilderPrivate(const SearchParameters&);
    UrlBuilderPrivate(UrlBuilderPrivate&&) = delete;
    UrlBuilderPrivate(const UrlBuilderPrivate&) = delete;
    UrlBuilderPrivate& operator=(const UrlBuilderPrivate&) = delete;
    UrlBuilderPrivate& operator=(const UrlBuilderPrivate&&) = delete;
    ~UrlBuilderPrivate() = default;
    void build();
    bool isValid() const;
    QUrl getUrl() const;

private:
    const QString API_URL = QStringLiteral("https://api.flickr.com/services/rest/?method=flickr.photos.search");
    SearchParameters mSearchParams;
    QUrl mUrl;
    bool mValid;
};

#endif
