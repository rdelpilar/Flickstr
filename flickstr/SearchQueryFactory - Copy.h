#ifndef SEARCHQUERYFACTORY_H
#define SEARCHQUERYFACTORY_H

#include "SearchQuery.h"

class SearchQueryFactory
{
public:
    SearchQueryFactory() = default;
    SearchQueryFactory(const QString&, const SearchQuery::Builder&, const QString&);
    SearchQueryFactory(SearchQueryFactory&&) = delete;
    SearchQueryFactory(const SearchQueryFactory&) = delete;
    SearchQueryFactory& operator=(const SearchQueryFactory&) = delete;
    SearchQueryFactory& operator=(const SearchQueryFactory&&) = delete;
    ~SearchQueryFactory() = default;

    SearchQuery build();

private:
    QString mTag;
    SearchQuery::Builder mQueryBuilder;
    QString mKey;
};

#endif
