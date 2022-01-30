#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtPlugin> 

#include "logtext.h"
#include "resultmodel.h"
#include "resultstatusitemmodel.h"
#include "resultmodelitem.h"
#include "manager.h"



#ifdef QT_STATIC
    Q_IMPORT_PLUGIN(QtQuick2Plugin)
    Q_IMPORT_PLUGIN(QtQuick2WindowPlugin)
    Q_IMPORT_PLUGIN(QtQuickLayoutsPlugin)
    Q_IMPORT_PLUGIN(QtQmlPlugin)
    Q_IMPORT_PLUGIN(QtQuickControls2Plugin)
    Q_IMPORT_PLUGIN(QtQuickControls1Plugin)
    Q_IMPORT_PLUGIN(QtQuickTemplates2Plugin)
#endif



int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);


    qmlRegisterType<LogText>("LogText",1,0,"LogText");
    qmlRegisterType<Manager>("Manager",1,0,"Manager");
    qmlRegisterType<ResultModel>("Model.ResultModel", 1, 0, "ResultModel");
    qmlRegisterType<ResultStatusItemModel>("Model.ResultStatusItemModel", 1, 0, "ResultStatusItemModel");
    qmlRegisterType<ResultModelItem>("Model.ResultModelItem", 1, 0, "ResultModelItem");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
