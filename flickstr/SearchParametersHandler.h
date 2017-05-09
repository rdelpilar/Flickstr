#ifndef SEARCHPARAMETERSHANDLER_H
#define SEARCHPARAMETERSHANDLER_H

#include "SearchParameters.h"

class SearchParametersHandler
{
public:
    SearchParametersHandler() = default;
    SearchParametersHandler(const QString&, const SearchParameters::Builder&, const QString&);
    SearchParametersHandler(SearchParametersHandler&&) = delete;
    SearchParametersHandler(const SearchParametersHandler&) = delete;
    SearchParametersHandler& operator=(const SearchParametersHandler&) = delete;
    SearchParametersHandler& operator=(const SearchParametersHandler&&) = delete;
    ~SearchParametersHandler() = default;

    SearchParameters build();

private:
    QString mTag;
    SearchParameters::Builder mQueryBuilder;
    QString mKey;
};

#endif
