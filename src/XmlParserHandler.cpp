#include "flickstr/XmlParserHandler.h"
#include "flickstr/XmlParserPublic.h"
#include "flickstr/XmlParserPrivate.h"

XmlParserHandler::XmlParserHandler(const QByteArray &byteArray,
                                   const RequestType &requestType)
    : mByteArray(byteArray),
      mRequestType(requestType)
{
}

std::shared_ptr<QStringListIterator> XmlParserHandler::parse()
{
    if(RequestType::PUBLIC_SEARCH == mRequestType) {
        XmlParserPublic parser(mByteArray);
        parse(parser);
        return parser.createIterator();
    } else if(RequestType::PRIVATE_SEARCH == mRequestType) {
        XmlParserPrivate parser(mByteArray);
        parse(parser);
        return parser.createIterator();
    }
}

template <typename T>
void XmlParserHandler::parse(T &parser)
{
    parser.parse();
}
