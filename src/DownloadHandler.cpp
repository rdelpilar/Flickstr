#include "flickstr/DownloadHandler.h"
#include "flickstr/Controller.h"

DownloadHandler::DownloadHandler(const SearchParameters &searchParams,
                                 const QUrl &url,
                                 const int index)
    : mSearchParams(searchParams),
      mUrl(url),
      mIndex(index),
      mUrlListIterator(nullptr),
      mRequestType(searchParams.getRequestType()),
      mXmlDownloader(nullptr),
      mPhotoDownloader(nullptr)
{
}

DownloadHandler::DownloadHandler(const SearchParameters &searchParams,
                                 const std::shared_ptr<QListIterator<QUrl>> &listIterator,
                                 const size_t size,
                                 const PhotoSize::Size &photoSize,
                                 const int index)
    : mSearchParams(searchParams),
      mUrl(QStringLiteral("")),
      mIndex(index),
      mUrlListIterator(listIterator),
      mSize(size),
      mPhotoSize(photoSize),
      mRequestType(RequestType::PHOTO_DOWNLOAD),
      mXmlDownloader(nullptr),
      mPhotoDownloader(nullptr)
{
}

void DownloadHandler::download()
{
    if(!mSearchParams.isValid() && mUrl.isEmpty())
        return;

    if(RequestType::PHOTO_DOWNLOAD == mRequestType) { // PHOTO
        mPhotoDownloader = std::make_shared<PhotoDownloader>(mUrlListIterator, mSize, mSearchParams, mPhotoSize, mIndex);

        connect(mPhotoDownloader.get(),
                SIGNAL(photoDownloadFinished(const QString&, const QUrl&, const QByteArray&, const size_t, const int)),
                Controller::provider(),
                SLOT(photoDownloadFinished(const QString&, const QUrl&, const QByteArray&, const size_t, const int)),
                static_cast<Qt::ConnectionType>(Qt::DirectConnection));

        download(mPhotoDownloader);
    } else { // XML
        mXmlDownloader = std::make_shared<XmlDownloader>(mSearchParams, mUrl, mIndex);

        connect(mXmlDownloader.get(),
                SIGNAL(xmlDownloadFinished(const SearchParameters&, const QByteArray&, const int)),
                Controller::provider(),
                SLOT(xmlDownloadFinished(const SearchParameters&, const QByteArray&, const int)),
                static_cast<Qt::ConnectionType>(Qt::DirectConnection));

        download(mXmlDownloader);
    }
}

template <typename T>
void DownloadHandler::download(T &downloader) const
{
    downloader->download();
}
