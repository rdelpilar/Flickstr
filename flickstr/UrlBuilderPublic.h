#ifndef URLBUILDERPUBLIC_H
#define URLBUILDERPUBLIC_H

#include <QUrl>

class UrlBuilderPublic
{
public:
    UrlBuilderPublic() = default;
    UrlBuilderPublic(const QString&);
    UrlBuilderPublic(UrlBuilderPublic&&) = delete;
    UrlBuilderPublic(const UrlBuilderPublic&) = delete;
    UrlBuilderPublic& operator=(const UrlBuilderPublic&) = delete;
    UrlBuilderPublic& operator=(const UrlBuilderPublic&&) = delete;
    ~UrlBuilderPublic() = default;
    void build();
    bool isValid() const;
    QUrl getUrl() const;

private:
    const QString API_URL = QStringLiteral("https://api.flickr.com/services/feeds/photos_public.gne?");
    QString mTag;
    QUrl mUrl;
    bool mValid;
};

#endif
