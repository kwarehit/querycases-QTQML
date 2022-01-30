#ifndef MANAGER_H
#define MANAGER_H

#include <memory>

#include <QObject>

#include "querythread.h"


class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);

    ~Manager();

     Q_INVOKABLE void start();
     Q_INVOKABLE QString getTutorials();
     Q_INVOKABLE QString getOneExample();

signals:
    void setEnabledQueryButton(bool b);

public slots:
    void onQueryTextChanged(const QString& text);

private slots:
    void setEnabled(bool b);

private:
    QueryThread* pThread_ = nullptr;

};

#endif // MANAGER_H
