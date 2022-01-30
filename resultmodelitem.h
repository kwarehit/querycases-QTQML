#ifndef RESULTMODELITEM_H
#define RESULTMODELITEM_H

#include <QObject>
#include <QMetaType>
#include <QString>
#include <QPair>
#include <QList>

#include "resulttype.h"

struct ResultDetails
{
    QString caseResult;
    QString caseTime;
    QString caseDet;
    QString caseSeq;
    QString caseMachine;
};

struct ResultItem
{
    QString caseType;
    QString caseName;
    QList<QPair<unsigned int, ResultDetails>> caseStatus;
};


class ResultModelItem : public QObject
{
    Q_OBJECT
public:
    explicit ResultModelItem(QObject *parent = nullptr);


    QString& getCaseType(int row);
    QString& getCaseName(int row);
    QList<QPair<unsigned int, ResultDetails>>& getCaseStatus(int row);
    int rowCount();
    void clear();

signals:
    void dateDone(ResultModelItem* pData);
    void clearView();

public slots:
    void setSourceData(const ResultType& caseResult);

private:

    QList<ResultItem> resultData_;

};









#endif // RESULTMODELITEM_H
