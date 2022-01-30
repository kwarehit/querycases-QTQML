#include "resultmodel.h"

#include "log.h"

ResultModel::ResultModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

ResultModel::~ResultModel()
{
    clearSubTables();
}

QHash<int, QByteArray> ResultModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { CaseTypeRole, "casetype" },
        { CaseNameRole, "casename" }
    };

    return roles;
}

void ResultModel::onDataDone(ResultModelItem* pData)
{
    BOOST_LOG(queryLog::get()) << "Start to update Results UI" << std::endl;

    resultData_ = pData;
    update();
}

ResultStatusItemModel* ResultModel::getSubModel(int row)
{
    if(row >= rowCount() || row < 0)
    {
        return nullptr;
    }

    auto pSub = new ResultStatusItemModel(this);
    pSub->setResultData(resultData_);
    pSub->setCurrentRow(row);
    subTableModels_.push_back(pSub);
    return pSub;
}

int ResultModel::rowCount(const QModelIndex &) const
{
    if(!resultData_)
    {
        return 0;
    }

    return resultData_->rowCount();
}

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < rowCount())
    {
        switch (role)
        {
        case CaseTypeRole:
            return resultData_->getCaseType(index.row());

        case CaseNameRole:
            return resultData_->getCaseName(index.row());

        default:
            return QVariant();
        }

    }
    return QVariant();
}

QVariant ResultModel::getCaseName(int row) const
{
    return resultData_->getCaseName(row);
}

void ResultModel::clearSubTables()
{
    for(auto& p : subTableModels_)
    {
        delete p;
    }

    subTableModels_.clear();
}

void ResultModel::clear()
{
    if(rowCount() <= 0)
    {
        return;
    }

    for(auto i = 0; i < rowCount(); ++i)
    {
        subTableModels_[i]->setCurrentRow(i);
        subTableModels_[i]->clear();
        delete subTableModels_[i];
    }

    subTableModels_.clear();

    beginRemoveRows(QModelIndex(), 0, rowCount()-1);
    endRemoveRows();
}

void ResultModel::update()
{
    clearSubTables();
    for(auto i = 0; i < rowCount(); ++i)
    {
        auto pSub = new ResultStatusItemModel(this);
        pSub->setResultData(resultData_);
        pSub->setCurrentRow(i);
        pSub->update();
        subTableModels_.push_back(pSub);
    }

    beginInsertRows(QModelIndex(), 0, rowCount()-1);
    endInsertRows();
}






