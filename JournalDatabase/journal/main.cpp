#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "journalmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    JournalManager backendManager;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("Backend", &backendManager);

    engine.loadFromModule("journal", "Main");

    return app.exec();
}