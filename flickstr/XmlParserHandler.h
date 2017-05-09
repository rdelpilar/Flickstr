#ifndef XMLPARSERHANDLER_H
#define XMLPARSERHANDLER_H

#include "SearchParameters.h"
#include "HttpRequest.h"

class XmlParserHandler
{
public:
    XmlParserHandler() = default;
    XmlParserHandler(const QByteArray&, const RequestType&);
    XmlParserHandler(XmlParserHandler&&) = delete;
    XmlParserHandler(const XmlParserHandler&) = delete;
    XmlParserHandler& operator=(const XmlParserHandler&) = delete;
    XmlParserHandler& operator=(const XmlParserHandler&&) = delete;
    ~XmlParserHandler() = default;

    std::shared_ptr<QStringListIterator> parse();

private:
    template <typename T>
    void parse(T&);

private:
    QByteArray mByteArray;
    RequestType mRequestType;
};

#endif
