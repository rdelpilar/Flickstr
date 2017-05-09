#include "flickstr/SearchParametersHandler.h"

SearchParametersHandler::SearchParametersHandler(const QString &tag,
                                                 const SearchParameters::Builder &queryBuilder,
                                                 const QString &key)
    : mTag(tag),
      mQueryBuilder(queryBuilder),
      mKey(key)
{
}

auto SearchParametersHandler::build() -> decltype(mQueryBuilder.build())
{
    if(mTag.isNull() || mTag.isEmpty())
        return SearchParameters();

    SearchParameters query;
    auto hasKey(!mKey.isEmpty());

    if(hasKey) {
        query = mQueryBuilder
                .setKey(mKey)
                .setTag(mTag)
                .setRequestType(RequestType::PRIVATE_SEARCH)
                .build();
    } else {
        query = mQueryBuilder
                .setTag(mTag)
                .setRequestType(RequestType::PUBLIC_SEARCH)
                .build();
    }

    return query;
}
