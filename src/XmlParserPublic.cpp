#include "flickstr/XmlParserPublic.h"

#include <QtXmlPatterns/QXmlQuery>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <algorithm>

// The following query will result in alternating urls
// eg:
// 0. content
// 1. link
// 2. content
// 3. link
// 4. ...
// query.setQuery(QString("%1%2")
// .arg(xmlNamespace)
// .arg("for $x in /feed/entry return ($x/content/string(),
// $x/link[@rel='enclosure']/@href/string())"));

// The query used in this function will store all 10 items in entry/content/string()
// in the first half of the list container. The other half:
// link[@rel='enclosure']/@href/string() will be appended after

XmlParserPublic::XmlParserPublic(const QByteArray &byteArray)
    : mByteArray(byteArray)
{
}

void XmlParserPublic::parse()
{
    if(mByteArray.size() <= 0)
        return;

    QXmlQuery query;
    query.setFocus(mByteArray);
    query.setQuery(QString("%1%2")
                   .arg(mXmlNamespace)
                   .arg("let $content := (/feed/entry/content/string()) "
                        "return ($content)"));

    if(query.isValid()) {
        query.evaluateTo(&mSmallImageList);
        extractSmallImageLinks();
    }
}

// The following query will result in extracting all URLs
// where the first half (content) will be stored in the list first
// then the other half (link) will be stored next. So, it's not
// alternating unlike the query above.
//query.setQuery(QString("%1%2")
//               .arg(xmlNamespace)
//               .arg("let $x := (/feed/entry) "
//                    "let $content := ($x/content/string()) "
//                    "let $link := ($x/link[@rel='enclosure']/@href/string()) "
//                    "return ($content, $link)"));

// Use the above query to this function
//void PublicTagSearchXml::extractSmallImageLinks()
//{
//    // These two REs works as well
//    // Use match.captured(1)
//    // QRegularExpression re("<img[^>]+src\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
//    // QRegularExpression re("<img[^>]*src=['|\"](.*?)['|\"].*?>");

//    QRegularExpression re("<img[^>]*src=[\"']([^\"^']*)");
//    QRegularExpressionMatch match;

//    auto middle = std::begin(mSmallAndLargeImageList) +
//            (mSmallAndLargeImageList.size() / 2);
//    std::for_each(std::begin(mSmallAndLargeImageList),
//                  middle,
//                  [&match, &re](QString& s) {
//                        match = re.match(s);
//                        if(match.hasMatch()) {
//                            s = match.captured(1);
//                        }
//    });
//}

void XmlParserPublic::extractSmallImageLinks()
{
    // These two REs works as well
    // Use match.captured(1)
    // QRegularExpression re("<img[^>]+src\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
    // QRegularExpression re("<img[^>]*src=['|\"](.*?)['|\"].*?>");

    QRegularExpression re("<img[^>]*src=[\"']([^\"^']*)");
    QRegularExpressionMatch match;

    std::for_each(std::begin(mSmallImageList),
                  std::end(mSmallImageList),
                  [&match, &re](QString& s) {
                        match = re.match(s);
                        if(match.hasMatch()) {
                            s = match.captured(1);
                        }
    });
}

std::shared_ptr<QStringListIterator> XmlParserPublic::createIterator()
{
    return std::make_shared<QStringListIterator>(mSmallImageList);
}
