#ifndef PHOTOSIZE_H
#define PHOTOSIZE_H

#include <map>
#include <QString>

struct PhotoSize
{
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
};

inline QString enumToSizeLabel(const PhotoSize::Size s) {
    const std::map<PhotoSize::Size, const QString> enumLabel {
        { PhotoSize::Size::SmallSquare_75, "SmallSquare_75" },
        { PhotoSize::Size::LargeSquare_150, "LargeSquare_150" },
        { PhotoSize::Size::Thumbnail_100, "Thumbnail_100" },
        { PhotoSize::Size::Small_240, "Small_240" },
        { PhotoSize::Size::Small_320, "Small_320"  },
        { PhotoSize::Size::Medium_500, "Medium_500" },
        { PhotoSize::Size::Medium_640, "Medium_640" },
        { PhotoSize::Size::Medium_800, "Medium_800" },
        { PhotoSize::Size::Large_1024, "Large_1024" },
        { PhotoSize::Size::Large_1600, "Large_1600" },
        { PhotoSize::Size::Large_2048, "Large_2048" },
        { PhotoSize::Size::Original, "Original" }
    };
    auto it = enumLabel.find(s);
    return it == enumLabel.end() ? "Unknown size" : it->second;
}

inline PhotoSize::Size SizeLabelToEnum(const QString &s) {
    const std::map<const QString, PhotoSize::Size> enumLabel {
        { "SmallSquare_75", PhotoSize::Size::SmallSquare_75 },
        { "LargeSquare_150", PhotoSize::Size::LargeSquare_150 },
        { "Thumbnail_100", PhotoSize::Size::Thumbnail_100 },
        { "Small_240", PhotoSize::Size::Small_240 },
        { "Small_320", PhotoSize::Size::Small_320 },
        { "Medium_500", PhotoSize::Size::Medium_500 },
        { "Medium_640", PhotoSize::Size::Medium_640 },
        { "Medium_800", PhotoSize::Size::Medium_800 },
        { "Large_1024", PhotoSize::Size::Large_1024 },
        { "Large_1600", PhotoSize::Size::Large_1600},
        { "Large_2048", PhotoSize::Size::Large_2048 },
        { "Original", PhotoSize::Size::Original }
    };
    auto it = enumLabel.find(s);
    return it == enumLabel.end() ? PhotoSize::Size::Medium_640 : it->second;
}

inline QString enumToSizeSuffix(const PhotoSize::Size s) {
    const std::map<PhotoSize::Size, const QString> enumSuffix {
        { PhotoSize::Size::SmallSquare_75, "_s" },
        { PhotoSize::Size::LargeSquare_150, "_q" },
        { PhotoSize::Size::Thumbnail_100, "_t" },
        { PhotoSize::Size::Small_240, "_m" },
        { PhotoSize::Size::Small_320, "_n"  },
        { PhotoSize::Size::Medium_500, "_-" },
        { PhotoSize::Size::Medium_640, "_z" },
        { PhotoSize::Size::Medium_800, "_c" },
        { PhotoSize::Size::Large_1024, "_b" },
        { PhotoSize::Size::Large_1600, "_h" },
        { PhotoSize::Size::Large_2048, "_k" },
        { PhotoSize::Size::Original, "_o" }
    };
    auto it = enumSuffix.find(s);
    return it == enumSuffix.end() ? QStringLiteral("Unknown size") : it->second;
}

#endif
