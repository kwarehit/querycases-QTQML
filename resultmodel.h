#ifndef RESULTMODEL_H
#define RESULTMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "resultmodelitem.h"
#include "resultstatusitemmodel.h"

class ResultModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ResultModel(QObject *parent = nullptr);

    ~ResultModel();

    enum ResultCaseRole {
        CaseTypeRole = Qt::DisplayRole,
        CaseNameRole = Qt::ToolTipRole,
    };
    Q_ENUM(ResultCaseRole)

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant getCaseName(int row) const;
    Q_INVOKABLE ResultStatusItemModel* getSubModel(int row);

signals:


public slots:
    void onDataDone(ResultModelItem* pData);
    void clear();

protected:
    void update();
    void clearSubTables();

    ResultModelItem* resultData_ = nullptr;
    QList<ResultStatusItemModel*> subTableModels_;

};

#endif // RESULTMODEL_H
