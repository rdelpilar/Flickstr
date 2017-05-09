#ifndef XMLPARSERINTERFACE_H
#define XMLPARSERINTERFACE_H

#include <QStringListIterator>

class XmlParserInterface
{
public:
    XmlParserInterface() = default;
    XmlParserInterface(XmlParserInterface&&) = delete;
    XmlParserInterface(const XmlParserInterface&) = delete;
    XmlParserInterface& operator=(const XmlParserInterface&) = delete;
    XmlParserInterface& operator=(const XmlParserInterface&&) = delete;
    virtual ~XmlParserInterface() = default;

    virtual void parse() = 0;
    virtual QStringListIterator createIterator() = 0;
};

#endif
