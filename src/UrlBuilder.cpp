#include <memory>
#include "flickstr/SearchParameters.h"
#include "flickstr/UrlBuilder.h"
#include "flickstr/UrlBuilderPublic.h"
#include "flickstr/UrlBuilderPrivate.h"

UrlBuilder::UrlBuilder(const SearchParameters &searchParams)
    : mSearchParams(searchParams)
{
}

QUrl UrlBuilder::build()
{
    auto requestType = mSearchParams.getRequestType();
    QUrl url(QStringLiteral(""));

    if(RequestType::PUBLIC_SEARCH == requestType) {
        UrlBuilderPublic builderPublic(mSearchParams.getTag());
        buildUrl(builderPublic);
        url = builderPublic.getUrl();
    } else if(RequestType::PRIVATE_SEARCH == requestType) {
        UrlBuilderPrivate builderPrivate(mSearchParams);
        buildUrl(builderPrivate);
        url = builderPrivate.getUrl();
    }

    return url;
}

template <typename T>
void UrlBuilder::buildUrl(T &query) const
{
    query.build();
}
