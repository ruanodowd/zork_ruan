#include "mainwindow.h"
#include "GraphNode.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QApplication>

using namespace GraphParser;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
