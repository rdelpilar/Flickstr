#ifndef URLBUILDER_H
#define URLBUILDER_H

#include <QUrl>
#include "SearchParameters.h"

class UrlBuilder
{
public:
    UrlBuilder() = default;
    UrlBuilder(const SearchParameters&);
    UrlBuilder(UrlBuilder&&) = delete;
    UrlBuilder(const UrlBuilder&) = delete;
    UrlBuilder& operator=(const UrlBuilder&) = delete;
    UrlBuilder& operator=(const UrlBuilder&&) = delete;
    ~UrlBuilder() = default;

    QUrl build();

private:
    template <typename T>
    void buildUrl(T&) const;

private:
    SearchParameters mSearchParams;
};

#endif
