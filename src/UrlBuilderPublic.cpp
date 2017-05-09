#include "flickstr/UrlBuilderPublic.h"
#include "flickstr/SearchParameters.h"

UrlBuilderPublic::UrlBuilderPublic(const QString &tag)
    : mTag(tag),
      mUrl(QStringLiteral("")),
      mValid(false)
{
}

void UrlBuilderPublic::build()
{
//    if(mTag.isNull() || mTag.isEmpty()) {
//        return;
//    }

    QString tagKey(::enumToParamLabel(SearchParamsKey::Type::TAGS));

    mTag.simplified();
    mTag.replace(" ", "+");
    mUrl = QString("%1%2%3%4")
            .arg(API_URL)
            .arg(tagKey)
            .arg(QChar('='))
            .arg(mTag);

    mValid = mUrl.isValid();
}

bool UrlBuilderPublic::isValid() const
{
    return mValid;
}

QUrl UrlBuilderPublic::getUrl() const
{
    return mUrl;
}
