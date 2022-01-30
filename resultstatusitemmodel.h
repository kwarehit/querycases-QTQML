#ifndef RESULTSTATUSITEMMODEL_H
#define RESULTSTATUSITEMMODEL_H

#include <QAbstractTableModel>

#include "resultmodelitem.h"


class ResultStatusItemModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ResultStatusItemModel(QObject *parent = nullptr);

    enum ResultItemRole {
        CaseCodeLineRole = Qt::DisplayRole,
        CaseResultRole = Qt::UserRole,
        CaseTimeRole = Qt::UserRole+1,
        CaseDetRole = Qt::UserRole+2,
        CaseSeqRole = Qt::UserRole+3,
        CaseMachineRole = Qt::UserRole+4,
    };
    Q_ENUM(ResultItemRole)

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    int columnCount(const QModelIndex &) const override;


    void setResultData(ResultModelItem* pData);
    void setCurrentRow(int row);
    void clear();
    void update();

signals:


private:
    ResultModelItem* resultData_ = nullptr;
    int currentRow_ = -1;
};

#endif // RESULTSTATUSITEMMODEL_H
