#include "flickstr/SearchParameters.h"

SearchParameters::SearchParameters()
    : mRequestType(RequestType::PUBLIC_SEARCH),
      mApiKey(QStringLiteral("")),
      mTag(QStringLiteral("")),
      mContentType(QStringLiteral("")),
      mPerPage(QStringLiteral("")),
      mPage(QStringLiteral(""))
{
}

SearchParameters::SearchParameters(const RequestType &requestType,
                         const QString &key,
                         const QString &tag,
                         const QString &contentType,
                         const QString &perPage,
                         const QString &page)
    : mRequestType(requestType),
      mApiKey(key),
      mTag(tag),
      mContentType(contentType),
      mPerPage(perPage),
      mPage(page)
{
}

// Copy constructor
SearchParameters::SearchParameters(const SearchParameters &rhs) noexcept
    : mRequestType(rhs.mRequestType),
      mApiKey(rhs.mApiKey),
      mTag(rhs.mTag),
      mContentType(rhs.mContentType),
      mPerPage(rhs.mPerPage),
      mPage(rhs.mPage)
{
}

// Move constructor
SearchParameters::SearchParameters(SearchParameters &&rhs) noexcept
    : mRequestType(rhs.mRequestType),
      mApiKey(rhs.mApiKey),
      mTag(rhs.mTag),
      mContentType(rhs.mContentType),
      mPerPage(rhs.mPerPage),
      mPage(rhs.mPage)
{
}

// Copy assignment operator
SearchParameters& SearchParameters::operator=(const SearchParameters &rhs) noexcept
{
    if(this == &rhs)
        return *this;
    SearchParameters tmp(rhs);
    *this = std::move(tmp);

    return *this;
}

// Move assignment operator
SearchParameters& SearchParameters::operator=(SearchParameters &&rhs) noexcept
{
    mRequestType = rhs.mRequestType;
    mApiKey = rhs.mApiKey;
    mTag = rhs.mTag;
    mContentType = rhs.mContentType;
    mPerPage = rhs.mPerPage;
    mPage = rhs.mPage;

    return *this;
}

SearchParameters::~SearchParameters() noexcept
{
}

auto SearchParameters::getRequestType() const -> RequestType
{
    return mRequestType;
}

auto SearchParameters::getApiKey() const -> QString
{
    return mApiKey;
}

auto SearchParameters::getTag() const -> QString
{
    return mTag;
}

auto SearchParameters::getContentType() const -> QString
{
    return mContentType;
}

auto SearchParameters::getPerPage() const -> QString
{
    return mPerPage;
}

auto SearchParameters::getPage() const -> QString
{
    return mPage;
}

bool SearchParameters::isValid() const
{
//    bool bValid = false;
//    if(!mTag.isEmpty())
//        bValid = true;

//    return bValid;
    return true;
}

// Builder class default constructor
SearchParameters::Builder::Builder()
    : mRequestType(RequestType::PUBLIC_SEARCH),
      mApiKey(::enumToDefArg(SearchParamsKey::Type::API_KEY)),
      mTag(::enumToDefArg(SearchParamsKey::Type::TAGS)),
      mContentType(::enumToDefArg(SearchParamsKey::Type::CONTENT_TYPE)),
      mPerPage(::enumToDefArg(SearchParamsKey::Type::PER_PAGE)),
      mPage(::enumToDefArg(SearchParamsKey::Type::PAGE))
{
}

// Copy constructor
SearchParameters::Builder::Builder(const SearchParameters::Builder &rhs) noexcept
    : mRequestType(rhs.mRequestType),
      mApiKey(rhs.mApiKey),
      mTag(rhs.mTag),
      mContentType(rhs.mContentType),
      mPerPage(rhs.mPerPage),
      mPage(rhs.mPage)
{
}

// Move constructor
SearchParameters::Builder::Builder(SearchParameters::Builder &&rhs) noexcept
    : mRequestType(rhs.mRequestType),
      mApiKey(rhs.mApiKey),
      mTag(rhs.mTag),
      mContentType(rhs.mContentType),
      mPerPage(rhs.mPerPage),
      mPage(rhs.mPage)
{
}

// Copy assignment operator
SearchParameters::Builder& SearchParameters::Builder::operator=(const SearchParameters::Builder &rhs) noexcept
{
    if(this == &rhs)
        return *this;
    Builder tmp(rhs);
    *this = std::move(tmp);
    return *this;
}

// Move assignment operator
SearchParameters::Builder& SearchParameters::Builder::operator=(SearchParameters::Builder &&rhs) noexcept
{
    mRequestType = rhs.mRequestType;
    mApiKey = rhs.mApiKey;
    mTag = rhs.mTag;
    mContentType = rhs.mContentType;
    mPerPage = rhs.mPerPage;
    mPage = rhs.mPage;
    return *this;
}

SearchParameters::Builder::~Builder()
{
}

auto SearchParameters::Builder::setKey(const QString &key) -> decltype(*this)
{
    this->mApiKey = key;
    return *this;
}

auto SearchParameters::Builder::setTag(const QString &tag) -> decltype(*this)
{
    this->mTag = tag;
    return *this;
}

auto SearchParameters::Builder::setContentType(const QString &contentType) -> decltype(*this)
{
    this->mContentType = contentType;
    return *this;
}

auto SearchParameters::Builder::setPerPage(const QString &perPage) -> decltype(*this)
{
    this->mPerPage = perPage;
    return *this;
}

auto SearchParameters::Builder::setPage(const QString &page) -> decltype(*this)
{
    this->mPage = page;
    return *this;
}

auto SearchParameters::Builder::setRequestType(const RequestType &requestType) -> decltype(*this)
{
    this->mRequestType = requestType;
    return *this;
}

auto SearchParameters::Builder::build() -> SearchParameters
{
    if(mTag.isNull() || mTag.isEmpty())
        return SearchParameters();

    return SearchParameters(this->mRequestType,
                            this->mApiKey,
                            this->mTag,
                            this->mContentType,
                            this->mPerPage,
                            this->mPage);
}
