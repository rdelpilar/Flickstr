#include "flickstr/UrlBuilderPrivate.h"

UrlBuilderPrivate::UrlBuilderPrivate(const SearchParameters &searchParams)
    : mSearchParams(searchParams),
      mUrl(QStringLiteral("")),
      mValid(false)
{
}

// Refactor
void UrlBuilderPrivate::build()
{
    if(!mSearchParams.isValid())
        return;

    auto tag(mSearchParams.getTag());
    tag.simplified();
    tag.replace(" ", "+");

    auto key(mSearchParams.getApiKey());
    auto contentType(mSearchParams.getContentType());
    auto page(mSearchParams.getPage());
    auto perPage(mSearchParams.getPerPage());

    QString keyParam(::enumToParamLabel(SearchParamsKey::Type::API_KEY));
    QString tagParam(::enumToParamLabel(SearchParamsKey::Type::TAGS));
    QString contentTypeParam(::enumToParamLabel(SearchParamsKey::Type::CONTENT_TYPE));
    QString pageParam(::enumToParamLabel(SearchParamsKey::Type::PAGE));
    QString perPageParam(::enumToParamLabel(SearchParamsKey::Type::PER_PAGE));

    mUrl = QString("%1%2%3%4%5%6%7%8%9%10%11%12%13%14%15%16%17%18%19%20%21")
            .arg(API_URL)
            .arg(QChar('&')).arg(keyParam).arg(QChar('=')).arg(key)
            .arg(QChar('&')).arg(tagParam).arg(QChar('=')).arg(tag)
            .arg(QChar('&')).arg(contentTypeParam).arg(QChar('=')).arg(contentType)
            .arg(QChar('&')).arg(pageParam).arg(QChar('=')).arg(page)
            .arg(QChar('&')).arg(perPageParam).arg(QChar('=')).arg(perPage);

    mValid = mUrl.isValid();
}

bool UrlBuilderPrivate::isValid() const
{
    return mValid;
}

QUrl UrlBuilderPrivate::getUrl() const
{
    return mUrl;
}
