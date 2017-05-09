#include "flickstr/RssModel.h"

RssModel::RssModel(QObject *parent)
    : QAbstractListModel(parent),
      mParentIndex(0),
      mTag(""),
      mRssModelList(QList<Rss>())
{
}

RssModel::RssModel(const QString &tag, QObject *parent)
    : QAbstractListModel(parent),
      mParentIndex(0),
      mTag(tag),
      mRssModelList(QList<Rss>())
{
}

// Copy constructor
RssModel::RssModel(const RssModel &rhs) noexcept
    : QAbstractListModel(nullptr),
      mRssModelList(rhs.mRssModelList)
{
}

// Move constructor
RssModel::RssModel(RssModel &&rhs) noexcept
    : mRssModelList(rhs.mRssModelList)
{
}

// Copy assignment operator
RssModel& RssModel::operator=(const RssModel &rhs) noexcept
{
    if(this == &rhs)
        return *this;
    RssModel tmp(rhs);
    *this = std::move(tmp);

    return *this;
}

// Move assignment operator
RssModel& RssModel::operator=(RssModel &&rhs) noexcept
{
    mRssModelList = rhs.mRssModelList;
    return *this;
}

RssModel::~RssModel()
{

}

void RssModel::addRss(const Rss& rss)
{
    auto item = rss;
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mRssModelList << std::move(item);
    endInsertRows();
}

int RssModel::getSize() const
{
    return mRssModelList.count();
}

void RssModel::setParentIndex(const int index)
{
    mParentIndex = index;
}

RssModel::RssModelRoles RssModel::getPhotoDataRole() const
{
    return PhotoDataRole;
}

int RssModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mRssModelList.count();
}

//Qt::ItemFlags TagInfoModel::flags(const QModelIndex &index) const
//{
//    if(!index.isValid())
//        return Qt::ItemIsEnabled;

//    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
//}

//bool TagInfoModel::removeRows(int row, int count, const QModelIndex &parent)
//{
//    beginRemoveRows(QModelIndex(), position, position+rows-1);

//    for(int row = 0; row < rows; ++row) {
//        mModelData.removeAt(position);
//    }

//    endRemoveRows();
//    return true;
//}

// Only insert item at end of list (Append) since photos will be downloaded and appended
// as needed on canfetchmore();
//bool TagInfoModel::insertRows(int row, int count, const QModelIndex &parent)
//{
//    beginInsertRows(QModelIndex(), position, position+rows-1);

//    //mModelData.push_back();

//    endInsertColumns();
//    return true;
//}


QVariant RssModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= mRssModelList.count())
        return QVariant();

    const Rss &rss = mRssModelList[index.row()];

    if(role == TagLabelRole) {
       return mTag;
    } else if(role == UrlRole) {
        return rss.getUrl();
    } else if(role == FilenameRole) {
        return rss.getFilename();
    } else if(role == PhotoWidthRole) {
        return rss.getPhotoRect().width();
    } else if(role == PhotoHeightRole) {
        return rss.getPhotoRect().height();
    } else if(role == PhotoDataRole) {
        Rss rssItem(rss);
        return QVariant::fromValue(rssItem.getData().get());
    } else if(role == PhotoThumbnailRole) {
        return QString("%1/%2/%3/%4/%5")
                .arg("image://ImageProvider")
                .arg(mParentIndex)
                .arg(index.row())
                .arg(QStringLiteral("Thumbnail"))
                .arg(QDateTime::currentDateTime().toString("dd-MM-yyyy:hh.mm.ss"));
    } else if(role == PhotoHighQualityRole) {
        return QString("%1/%2/%3/%4/%5")
                .arg("image://ImageProvider")
                .arg(mParentIndex)
                .arg(index.row())
                .arg(QStringLiteral("HighQuality"))
                .arg(QDateTime::currentDateTime().toString("dd-MM-yyyy:hh.mm.ss"));
    } else if(role == PhotoRoiXRole) {
        return rss.getPhotoROIRect().x();
    } else if(role == PhotoRoiYRole) {
        return rss.getPhotoROIRect().y();
    } else if(role == PhotoRoiWidthRole) {
        return rss.getPhotoROIRect().width();
    } else if(role == PhotoRoiHeightRole) {
        return rss.getPhotoROIRect().height();
    } else {
        return QVariant();
    }
}

void RssModel::resetRssModel()
{
    beginResetModel();
    mTag.clear();
    mRssModelList.clear();
    endResetModel();
}

//bool TagInfoModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if(index.isValid() && role == Qt::EditRole) {
//        const TagInfo &tagInfo = mModelData[index.row()];
//        //tagInfo.setPhotoROIRect(QRect()); // TODO
//        emit dataChanged(index, index);
//        return true;
//    }

//    return false;
//}

QHash<int, QByteArray> RssModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TagLabelRole] = "TagLabelRole";
    roles[UrlRole] = "UrlRole";
    roles[FilenameRole] = "FilenameRole";
    roles[PhotoWidthRole] = "PhotoWidthRole";
    roles[PhotoHeightRole] = "PhotoHeightRole";
    roles[PhotoDataRole] = "PhotoDataRole";
    roles[PhotoThumbnailRole] = "PhotoThumbnailRole";
    roles[PhotoHighQualityRole] = "PhotoHighQualityRole";
    roles[PhotoRoiXRole] = "PhotoRoiXRole";
    roles[PhotoRoiYRole] = "PhotoRoiYRole";
    roles[PhotoRoiWidthRole] = "PhotoRoiWidthRole";
    roles[PhotoRoiHeightRole] = "PhotoRoiHeightRole";
    return roles;
}

QString RssModel::tag() const
{
    return mTag;
}

void RssModel::setTag(const QString &tag)
{
    mTag = tag;
}
