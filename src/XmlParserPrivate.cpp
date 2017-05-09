#include "flickstr/XmlParserPrivate.h"

#include <QtXmlPatterns/QXmlQuery>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <algorithm>

XmlParserPrivate::XmlParserPrivate(const QByteArray &byteArray)
    : mByteArray(byteArray),
      mPhotosAttributes(QStringLiteral("")),
      mPhotoAttributes(QStringList()),
      mError(ERROR::NO_ERROR)
{
}

void XmlParserPrivate::parse()
{
    if(mByteArray.size() <= 0)
        return;

    QXmlQuery query;
    query.setFocus(mByteArray);

    // Get error code if any
    // <rsp stat="fail">
    // <err code="100" msg="Invalid API Key (Key not found)"/>
    // </rsp>

    query.setQuery(QString("%1")
                   .arg("/rsp/@stat/string()"));
    QString s;
    query.evaluateTo(&s);
    if(s.simplified().compare(QStringLiteral("fail"), Qt::CaseSensitive) == 0) {
        query.setQuery(QString("%1")
                       .arg("/rsp/err/@code/string()"));
        query.evaluateTo(&s);
        if(s.simplified().compare("100",Qt::CaseSensitive) == 0) {
            mError = ERROR::INVALID_KEY;
        }
        return;
    }

    // Get photos attributes
    query.setQuery(QString("%1")
                   .arg("let $p := /rsp/photos "
                        "return "
                        "concat($p/@page,',',$p/@pages,',',$p/@perpage,',',$p/@total)"));
    if(!query.isValid()) {
        mError = ERROR::INVALID_QUERY;
        return;
    }

    query.evaluateTo(&s);
    mPhotosAttributes = s.simplified();

    // Below query will result in this: page=1 pages=2785 perpage=100 total=278425
    //    query.setQuery(QString("%1")
    //                   .arg("/rsp/photos/@*/(concat(name(.),'=',.))"));


    // Return a list of selected photo attributes
    // id,secret,server,farm
    // "31970906646,a91038624d,317,1"
    query.setQuery(QString("%1")
                   .arg("for $p in /rsp/photos/photo "
                        "return "
                        "concat($p/@id,':',$p/@secret,':',$p/@server,':',$p/@farm)"));

    if(!query.isValid()) {
        mError = ERROR::INVALID_QUERY;
        return;
    }

    query.evaluateTo(&mPhotoAttributes);
}

XmlParserPrivate::ERROR XmlParserPrivate::getError() const
{
    return mError;
}

std::shared_ptr<QStringListIterator> XmlParserPrivate::createIterator()
{
    return std::make_shared<QStringListIterator>(mPhotoAttributes);
}
