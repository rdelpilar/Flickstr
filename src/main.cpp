#include <QApplication>
#include <QQmlApplicationEngine>
#include "flickstr/Controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    auto p = qobject_cast<Controller *>(Controller::provider());
    p->init(&engine);
    return app.exec();
}
