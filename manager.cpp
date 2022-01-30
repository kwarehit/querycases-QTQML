#include "manager.h"

#include <thread>
#include <algorithm>
#include <numeric>
#include <set>

#include "log.h"
#include "emitter.h"
#include "collector.h"


Manager::Manager(QObject *parent)
    : QObject(parent)
{
    pThread_ = new QueryThread(this);
    pThread_->getCollector()->setCallBack(&Emitter::getResults);

    connect(pThread_, &QueryThread::enableButton, this, &Manager::setEnabled);
}

Manager::~Manager()
{
    delete pThread_;
}

QString Manager::getTutorials()
{
    return promptText;
}

QString Manager::getOneExample()
{
    return queryoneexample;
}

void Manager::onQueryTextChanged(const QString& text)
{
    try
    {
        auto listStr = text.split('\n', QString::SkipEmptyParts);
        std::string codeLine;
        std::string app;
        std::string changeList;
        std::set<std::string> cases;

        for(auto i = 0; i<listStr.size(); ++i)
        {
            QString s = listStr[i].trimmed();
            if(i == 0)
            {
                codeLine = s.toStdString();
            }
            else if(i == 1)
            {
                bool ok{};
                s.toInt(&ok, 10);
                if(ok)
                {
                    changeList = s.toStdString();
                }
                else
                {
                    app = s.toStdString();
                }
            }
            else if(i == 2 && app.empty())
            {
                app = s.toStdString();
            }
            else
            {
                cases.insert(s.toStdString());
            }
        }
        pThread_->refine(cases, codeLine, app, changeList);

    }
    catch (std::exception& ec)
    {
        BOOST_LOG(queryLog::get()) << ec.what() << std::endl;
    }
}

void Manager::setEnabled(bool b)
{
    Q_EMIT setEnabledQueryButton(b);
}


void Manager::start()
{
    pThread_->start();
}







