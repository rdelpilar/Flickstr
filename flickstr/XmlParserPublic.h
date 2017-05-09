#ifndef XMLPARSERPUBLIC_H
#define XMLPARSERPUBLIC_H

#include <QStringList>
#include <memory>

class XmlParserPublic
{
public:
    XmlParserPublic() = default;
    XmlParserPublic(const QByteArray&);
    XmlParserPublic(XmlParserPublic&&) = delete;
    XmlParserPublic(const XmlParserPublic&) = delete;
    XmlParserPublic& operator=(const XmlParserPublic&) = delete;
    XmlParserPublic& operator=(const XmlParserPublic&&) = delete;
    ~XmlParserPublic() {}

    void parse();
    std::shared_ptr<QStringListIterator> createIterator();

private:
    void extractSmallImageLinks();

private:
    QByteArray mByteArray;
    QStringList mSmallImageList;
    const QString mXmlNamespace = "declare default element namespace "
                                  "'http://www.w3.org/2005/Atom';";
};

#endif
