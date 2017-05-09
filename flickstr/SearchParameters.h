#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include <QString>
#include <map>
#include "HttpRequest.h"

struct SearchParamsKey {
    enum class Type { API_KEY = 0,
                      TAGS,
                      CONTENT_TYPE,
                      PER_PAGE,
                      PAGE
                    };
};

inline QString enumToParamLabel(const SearchParamsKey::Type e) {
    const std::map<SearchParamsKey::Type, const QString> enumLabel {
        { SearchParamsKey::Type::API_KEY, "api_key" },
        { SearchParamsKey::Type::TAGS, "tags" },
        { SearchParamsKey::Type::CONTENT_TYPE, "content_type" },
        { SearchParamsKey::Type::PER_PAGE, "per_page" },
        { SearchParamsKey::Type::PAGE, "page" }
    };

    auto it = enumLabel.find(e);
    return it == enumLabel.end() ? "Unknown Parameter" : it->second;
}

inline QString enumToDefArg(const SearchParamsKey::Type e) {
    const std::map<SearchParamsKey::Type, const QString> enumLabel {
        { SearchParamsKey::Type::API_KEY, "" },
        { SearchParamsKey::Type::TAGS, "" },
        { SearchParamsKey::Type::CONTENT_TYPE, "1" },
        { SearchParamsKey::Type::PER_PAGE, "50" },
        { SearchParamsKey::Type::PAGE, "1" }
    };

    auto it = enumLabel.find(e);
    return it == enumLabel.end() ? QStringLiteral("Unknown Parameter") : it->second;
}

class SearchParameters
{
public:
    SearchParameters();
    SearchParameters(const RequestType&,
                const QString&,
                const QString&,
                const QString&,
                const QString&,
                const QString&);

    SearchParameters(const SearchParameters&) noexcept;
    SearchParameters(SearchParameters&&) noexcept;
    SearchParameters& operator=(const SearchParameters&) noexcept;
    SearchParameters& operator=(SearchParameters&&) noexcept;
    ~SearchParameters() noexcept;

    RequestType getRequestType() const;
    QString getApiKey() const;
    QString getTag() const;
    QString getContentType() const;
    QString getPerPage() const;
    QString getPage() const;

    bool isValid() const;

private:
    RequestType mRequestType;
    QString mApiKey;
    QString mTag;
    QString mContentType;
    QString mPerPage;
    QString mPage;

public:
    class Builder {
    public:
        Builder();
        Builder(const Builder&) noexcept;
        Builder(Builder&&) noexcept;
        Builder& operator=(const Builder&) noexcept;
        Builder& operator=(Builder&&) noexcept;
        ~Builder() noexcept;

        Builder& setKey(const QString&);
        Builder& setTag(const QString&);
        Builder& setContentType(const QString&);
        Builder& setPerPage(const QString&);
        Builder& setPage(const QString&);
        Builder& setRequestType(const RequestType&);

        SearchParameters build();

    private:
        RequestType mRequestType;
        QString mApiKey;
        QString mTag;
        QString mContentType;
        QString mPerPage;
        QString mPage;
    };
};

#endif
