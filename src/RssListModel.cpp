#include "flickstr/RssListModel.h"


RssListModel::RssListModel(QObject *parent)
    : QAbstractListModel(parent),
      mModelList(QList<std::shared_ptr<RssModel>>())
{
}

RssListModel::RssListModel(RssListModel &&rhs) noexcept
    : mModelList(rhs.mModelList)
{
}

RssListModel::RssListModel(const RssListModel &rhs) noexcept
    : QAbstractListModel(nullptr),
      mModelList(rhs.mModelList)
{
}

RssListModel& RssListModel::operator=(const RssListModel &rhs) noexcept
{
    if(this == &rhs)
        return *this;
    RssListModel tmp(rhs);
    *this = std::move(tmp);
    return *this;
}

RssListModel& RssListModel::operator=(RssListModel &&rhs) noexcept
{
    mModelList = rhs.mModelList;
    return *this;
}

RssListModel::~RssListModel()
{

}

// Append dummy list model
void RssListModel::createDummyListModel()
{
    auto model(std::make_shared<RssModel>(QStringLiteral("")));
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    model->setParentIndex(rowCount());
    mModelList << std::move(model);
    endInsertRows();
}

// Remove one Rss model
void RssListModel::removeRssModel(const int index)
{
    if(index < 0 || index > mModelList.size()) return;

    beginRemoveRows(QModelIndex(), index, 1);
    mModelList.removeAt(index);
    endRemoveRows();
}

void RssListModel::resetRssModel(const int index)
{
    if(index < 0 || index > mModelList.size()) return;

    mModelList.at(index)->resetRssModel();
}

void RssListModel::setRssModelTag(const int index, QString &tag)
{
    if(index < 0 || index > mModelList.size()) return;

    mModelList.at(index)->setTag(tag);
}

bool RssListModel::rssModelTagEmpty(const int index) const
{
    return mModelList.at(index)->tag().isEmpty();
}

int RssListModel::getRssModelSize(const int index) const
{
    if(index < 0 || index > mModelList.size()) return -1;

    return mModelList.at(index)->getSize();
}

void RssListModel::addRss(const int index, const Rss &rss)
{
    if(index < 0 || index > mModelList.size()) return;

    mModelList.at(index)->addRss(std::move(rss));
}

int RssListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mModelList.count();
}

QVariant RssListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= mModelList.count())
        return QVariant();

    auto rssModel = mModelList[index.row()];

    if(RssModelRole == role) {
        return QVariant::fromValue(rssModel.get());
    } else {
        return QVariant();
    }
}

QHash<int, QByteArray> RssListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RssModelRole] = "RssModelRole";
    return roles;
}
