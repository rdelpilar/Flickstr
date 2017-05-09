#include <QApplication>
#include <QQmlApplicationEngine>
#include "flickstr/Controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<Controller>("ControllerLib",
                                         1,
                                         0,
                                         "Controller",
                                         &Controller::provider);
    engine.load(QUrl(QStringLiteral("qrc:///CoreQml/main.qml")));

    auto controller = qobject_cast<Controller*>(Controller);
    return app.exec();
}


// qobject_cast<SingletonController *>(SingletonController::provider());
// Controller::getInstance().init(engine);
