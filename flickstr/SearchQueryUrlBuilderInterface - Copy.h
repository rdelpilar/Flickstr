#ifndef SEARCHQUERYURLBUILDERINTERFACE_H
#define SEARCHQUERYURLBUILDERINTERFACE_H

#include <QUrl>

class SearchQueryUrlBuilderInterface
{
public:
    SearchQueryUrlBuilderInterface() = default;
    SearchQueryUrlBuilderInterface(SearchQueryUrlBuilderInterface&&) = delete;
    SearchQueryUrlBuilderInterface(const SearchQueryUrlBuilderInterface&) = delete;
    SearchQueryUrlBuilderInterface& operator=(const SearchQueryUrlBuilderInterface&) = delete;
    SearchQueryUrlBuilderInterface& operator=(const SearchQueryUrlBuilderInterface&&) = delete;
    virtual ~SearchQueryUrlBuilderInterface() = default;

    virtual void build() = 0;
    virtual bool isValid() const = 0;
    virtual QUrl getUrl() const = 0;
};

#endif
