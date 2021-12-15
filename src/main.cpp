#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "guimodel.h"
#include "datamodel.h"
#include "commit.h"
#include "key.h"
#include "stack.h"
#include "transaction.h"
#include <stdlib.h>

QString randomAddress() {
    char* hex = "0123456789ABCDEF";
    QString out = "";
    for(int i = 0; i < 64; i++) {
        out += hex[rand() % 16];
    }
    return out;
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    DataModel model = DataModel();
    model.addConstruct(new Key(randomAddress(), rand()%100000));
    model.addConstruct(new Key(randomAddress(), rand()%100000));
    model.addConstruct(new Key(randomAddress(), rand()%100000));
    model.addConstruct(new Stack(randomAddress(), randomAddress(), rand()%100000, randomAddress()));
    model.addConstruct(new Transaction(randomAddress(), randomAddress(), randomAddress()));
    for(int i = 0; i < 21; i++) {
        model.addCommit(new Commit(TYPE_SIGNATURE, randomAddress()));
    }
    model.addCommit(new Commit(TYPE_DECISION, randomAddress()));
    model.addCommit(new Commit(TYPE_DECISION, randomAddress()));

    QScopedPointer<GUIModel> guiPointer(new GUIModel(&model));

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
