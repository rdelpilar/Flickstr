#ifndef XMLPARSERPRIVATE_H
#define XMLPARSERPRIVATE_H

#include <QStringList>
#include <memory>

class XmlParserPrivate
{
public:
    enum class ERROR { NO_ERROR = 0, INVALID_KEY, INVALID_QUERY };
    XmlParserPrivate() = default;
    XmlParserPrivate(const QByteArray&);
    XmlParserPrivate(XmlParserPrivate&&) = delete;
    XmlParserPrivate(const XmlParserPrivate&) = delete;
    XmlParserPrivate& operator=(const XmlParserPrivate&) = delete;
    XmlParserPrivate& operator=(const XmlParserPrivate&&) = delete;
    ~XmlParserPrivate() {}

    void parse();
    ERROR getError() const;
    std::shared_ptr<QStringListIterator> createIterator();


private:
    QByteArray mByteArray;
    QString mPhotosAttributes;
    QStringList mPhotoAttributes;
    const QString mXmlNamespace = "declare default element namespace "
                                  "'http://www.w3.org/2005/Atom';";
    ERROR mError;
};

#endif
