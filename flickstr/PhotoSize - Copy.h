#ifndef PHOTOSIZE_H
#define PHOTOSIZE_H

#include <QString>
#include <QHash>

class PhotoSize
{
public:
    enum class Size {
        SmallSquare_75 = 0,
        LargeSquare_150,
        Thumbnail_100,
        Small_240,
        Small_320,
        Medium_500,
        Medium_640,
        Medium_800,
        Large_1024,
        Large_1600,
        Large_2048,
        Original
    };

    PhotoSize() = default;
    virtual ~PhotoSize() = default;

    virtual void setSize(const Size&) = 0;
    virtual Size getSize() const = 0;
    virtual void setSuffix(const Size&) = 0;
    virtual QString getSuffix() const = 0;
    virtual QString getName() const = 0;
};

typedef PhotoSize::Size SizeType;

const QHash<QString, SizeType> SizeSuffixTable({
                                        {"_s", SizeType::SmallSquare_75},
                                        {"_q", SizeType::LargeSquare_150},
                                        {"_t", SizeType::Thumbnail_100},
                                        {"_m", SizeType::Small_240},
                                        {"_n", SizeType::Small_320},
                                        {"_-", SizeType::Medium_500},
                                        {"_z", SizeType::Medium_640},
                                        {"_c", SizeType::Medium_800},
                                        {"_b", SizeType::Large_1024},
                                        {"_h", SizeType::Large_1600},
                                        {"_k", SizeType::Large_2048},
                                        {"_o", SizeType::Original}
                                    });

const QHash<QString, SizeType> SizeNameTable({
                                           {"SmallSquare_75", SizeType::SmallSquare_75},
                                           {"LargeSquare_150", SizeType::LargeSquare_150},
                                           {"Thumbnail_100", SizeType::Thumbnail_100},
                                           {"Small_240", SizeType::Small_240},
                                           {"Small_320", SizeType::Small_320},
                                           {"Medium_500", SizeType::Medium_500},
                                           {"Medium_640", SizeType::Medium_640},
                                           {"Medium_800", SizeType::Medium_800},
                                           {"Large_1024", SizeType::Large_1024},
                                           {"Large_1600", SizeType::Large_1600},
                                           {"Large_2048", SizeType::Large_2048},
                                           {"Original", SizeType::Original}
                                        });

class PhotoSizeBrowser : public PhotoSize
{
public:
    PhotoSizeBrowser()
        : mSize(SizeType::SmallSquare_75), mSuffix(SizeSuffixTable.key(mSize)) {}
    PhotoSizeBrowser(const Size &size, const QString &suffix)
        : mSize(size), mSuffix(suffix) {}
    virtual ~PhotoSizeBrowser() = default;

    virtual void setSize(const SizeType& size) {
        if(size == Size::SmallSquare_75)
            mSize = size;
        else if(size == Size::LargeSquare_150)
            mSize = size;
        else if(size == Size::Thumbnail_100)
            mSize = size;
        else if(size == Size::Small_240)
            mSize = size;
        else if(size == Size::Small_320)
            mSize = size;
        else if(size == Size::Medium_500)
            mSize = size;
    }

    virtual Size getSize() const {
        return mSize;
    }

    virtual void setSuffix(const SizeType& size) {
        mSuffix = SizeSuffixTable.key(size);
    }

    virtual QString getSuffix() const {
        return mSuffix;
    }

    virtual QString getName() const {
        return mName;
    }

private:
    Size mSize;
    QString mSuffix;
    const QString mName = {"Browser"};
};

class PhotoSizeAlbum : public PhotoSize
{
public:
    PhotoSizeAlbum()
        : mSize(SizeType::Small_240), mSuffix(SizeSuffixTable.key(mSize)) {}
    PhotoSizeAlbum(const Size &size, const QString &suffix)
        : mSize(size), mSuffix(suffix) {}
    virtual ~PhotoSizeAlbum() = default;

    virtual void setSize(const SizeType& size) {
        if(size == Size::SmallSquare_75)
            mSize = size;
        else if(size == Size::LargeSquare_150)
            mSize = size;
        else if(size == Size::Thumbnail_100)
            mSize = size;
        else if(size == Size::Small_240)
            mSize = size;
        else if(size == Size::Small_320)
            mSize = size;
        else if(size == Size::Medium_500)
            mSize = size;
    }

    virtual Size getSize() const {
        return mSize;
    }

    virtual void setSuffix(const SizeType& size) {
        mSuffix = SizeSuffixTable.key(size);
    }

    virtual QString getSuffix() const {
        return mSuffix;
    }

    virtual QString getName() const {
        return mName;
    }

private:
    Size mSize;
    QString mSuffix;
    const QString mName = {"Album"};
};

class PhotoSizeFullScreen : public PhotoSize
{
public:
    PhotoSizeFullScreen() : mSize(SizeType::Medium_640), mSuffix(SizeSuffixTable.key(mSize)) {}
    PhotoSizeFullScreen(const Size &size, const QString &suffix)
        : mSize(size), mSuffix(suffix) {}
    virtual ~PhotoSizeFullScreen() = default;

    virtual void setSize(const SizeType& size) {
        if(size == Size::Medium_640)
            mSize = size;
        else if(size == Size::Medium_800)
            mSize = size;
        else if(size == Size::Large_1024)
            mSize = size;
        else if(size == Size::Large_1600)
            mSize = size;
        else if(size == Size::Large_2048)
            mSize = size;
        else if(size == Size::Original)
            mSize = size;
    }

    virtual Size getSize() const {
        return mSize;
    }

    virtual void setSuffix(const SizeType& size) {
        mSuffix = SizeSuffixTable.key(size);
    }

    virtual QString getSuffix() const {
        return mSuffix;
    }

    virtual QString getName() const {
        return mName;
    }

private:
    Size mSize;
    QString mSuffix;
    const QString mName = {"FullScreen"};
};

class PhotoSizeDummy : public PhotoSize
{
public:
    PhotoSizeDummy() : mSize(SizeType::SmallSquare_75), mSuffix(SizeSuffixTable.key(mSize)) {}
    PhotoSizeDummy(const Size &size, const QString &suffix)
        : mSize(size), mSuffix(suffix) {}
    virtual ~PhotoSizeDummy() = default;

    virtual void setSize(const SizeType& size) {
        if(size == Size::Medium_640)
            mSize = size;
        else if(size == Size::Medium_800)
            mSize = size;
        else if(size == Size::Large_1024)
            mSize = size;
        else if(size == Size::Large_1600)
            mSize = size;
        else if(size == Size::Large_2048)
            mSize = size;
        else if(size == Size::Original)
            mSize = size;
    }

    virtual Size getSize() const {
        return mSize;
    }

    virtual void setSuffix(const SizeType& size) {
        mSuffix = SizeSuffixTable.key(size);
    }

    virtual QString getSuffix() const {
        return mSuffix;
    }

    virtual QString getName() const {
        return mName;
    }

private:
    Size mSize;
    QString mSuffix;
    const QString mName = {"Dummy"};
};

struct DefaultPhotoSize {
    DefaultPhotoSize() = default;
    PhotoSizeBrowser browser;
    PhotoSizeAlbum album;
    PhotoSizeFullScreen fullscreen;
    ~DefaultPhotoSize(){}
};

#endif
