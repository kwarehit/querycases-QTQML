#include "resultmodelitem.h"

#include <numeric>
#include <algorithm>
#include <iterator>

#include "emitter.h"
#include "log.h"


ResultModelItem::ResultModelItem(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<ResultType>();
    connect(&Emitter::instance(), &Emitter::addResults, this, &ResultModelItem::setSourceData);
}


void ResultModelItem::setSourceData(const ResultType& caseResult)
{
    BOOST_LOG(queryLog::get()) << "Start to set Results for UI" << std::endl;

    Q_EMIT clearView();

    resultData_.clear();

    auto toResultDetails = [](const auto& caseDetails)
    {
        return ResultDetails{
              QString::fromStdString(caseDetails.caseResult)
            , QString::fromStdString(caseDetails.caseTime)
            , QString::fromStdString(caseDetails.caseDet)
            , QString::fromStdString(caseDetails.caseSeq)
            , QString::fromStdString(caseDetails.caseMachine)
        };
    };

    for(auto&& item : caseResult)
    {
        ResultItem res;
        res.caseType = QString::fromStdString(item.first);

        for(auto&& itemCase: item.second)
        {
            res.caseName = QString::fromStdString(itemCase.first);

            QList<QPair<unsigned int, ResultDetails>> caseStatus;
            std::transform(itemCase.second.cbegin(), itemCase.second.cend(), std::back_inserter(caseStatus)
                           ,[&](auto& v){ return QPair{v.first, toResultDetails(v.second)}; });

            res.caseStatus = caseStatus;
            resultData_.push_back(res);
        }
    }

    Q_EMIT dateDone(this);
}


int ResultModelItem::rowCount()
{
    return resultData_.size();
}

QString& ResultModelItem::getCaseType(int row)
{
    return resultData_[row].caseType;
}

QString& ResultModelItem::getCaseName(int row)
{
    return resultData_[row].caseName;
}

QList<QPair<unsigned int, ResultDetails>>& ResultModelItem::getCaseStatus(int row)
{
    return resultData_[row].caseStatus;
}

void ResultModelItem::clear()
{
    resultData_.clear();
}





