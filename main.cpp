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


    try {
        // Example JSON string representing a graph node
        QString jsonString = R"({
            "id": "node1",
            "data": "some data",
            "edges": [
                {"id": "node2", "data": "edge data"},
                {"id": "node3", "data": 42}
            ]
        })";

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        QJsonObject jsonObj = jsonDoc.object();

        auto rootNode = JSONParser<GraphNode>::parse(jsonObj);
        std::cout << *rootNode << std::endl;

        // Convert back to JSON
        QJsonDocument generatedDoc(rootNode->toJSON());
        QString generatedJSON = generatedDoc.toJson(QJsonDocument::Compact);
        std::cout << "Generated JSON: " << generatedJSON.toStdString() << std::endl;
    } catch (const ParseException& ex) {
        std::cerr << "Failed to parse JSON: " << ex.what() << std::endl;
    }



    return a.exec();
}
