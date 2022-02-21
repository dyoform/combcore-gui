#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QProcess>
#include "guimodel.h"
#include "datamodel.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("COMBCore");
#endif

    QGuiApplication app(argc, argv);

    QString program = "./combcore";
    QProcess *daemon = new QProcess(&app);
    daemon->start(program);
    QObject::connect(&app, &QGuiApplication::aboutToQuit, daemon, [daemon]() {daemon->terminate();});

    DataModel* model = new DataModel();
    QObject::connect(daemon, &QProcess::readyReadStandardOutput, model, [model, daemon]() {model->appendOutput(daemon->readAllStandardOutput());});

    QScopedPointer<GUIModel> guiPointer(new GUIModel(model));

    qmlRegisterSingletonInstance("combcore.gui", 1, 0, "GUI", guiPointer.get());
    qmlRegisterSingletonType( QUrl("qrc:/Constants.qml"), "combcore.constants", 1, 0, "Constants");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
