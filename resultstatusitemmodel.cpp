#include "resultstatusitemmodel.h"




ResultStatusItemModel::ResultStatusItemModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

void ResultStatusItemModel::setResultData(ResultModelItem* pData)
{
    resultData_= pData;
}

void ResultStatusItemModel::setCurrentRow(int row)
{
    currentRow_ = row;
}

int ResultStatusItemModel::columnCount(const QModelIndex &) const
{
    return 6;
}

QHash<int, QByteArray> ResultStatusItemModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { CaseCodeLineRole, "casecodeline" },
        { CaseResultRole, "caseresult" },
        { CaseTimeRole, "casetime" },
        { CaseDetRole, "casedet" },
        { CaseSeqRole, "caseseq" },
        { CaseMachineRole, "casemachine" }
    };

    return roles;
}

int ResultStatusItemModel::rowCount(const QModelIndex &) const
{
    if(!resultData_)
    {
        return 0;
    }

    return resultData_->getCaseStatus(currentRow_).size();
}

QVariant ResultStatusItemModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < rowCount())
        switch (role)
        {
            case CaseCodeLineRole:
            {
                return resultData_->getCaseStatus(currentRow_).at(index.row()).first;
            }
            case CaseResultRole:
            {
                return resultData_->getCaseStatus(currentRow_).at(index.row()).second.caseResult;
            }
            case CaseTimeRole:
            {
                return resultData_->getCaseStatus(currentRow_).at(index.row()).second.caseTime;
            }
            case CaseDetRole:
            {
                return resultData_->getCaseStatus(currentRow_).at(index.row()).second.caseDet;
            }
            case CaseSeqRole:
            {
                return resultData_->getCaseStatus(currentRow_).at(index.row()).second.caseSeq;
            }
            case CaseMachineRole:
            {
                return resultData_->getCaseStatus(currentRow_).at(index.row()).second.caseMachine;
            }
            default:
                return QVariant();
        }
    return QVariant();
}

void ResultStatusItemModel::clear()
{
    if(rowCount() <= 0)
    {
        return;
    }

    beginRemoveRows(QModelIndex(), 0, rowCount()-1);
    endRemoveRows();
}

void ResultStatusItemModel::update()
{ 
    beginInsertRows(QModelIndex(), 0, rowCount()-1);
    endInsertRows();
}

