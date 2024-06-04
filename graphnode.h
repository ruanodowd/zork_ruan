#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <memory>
#include <exception>
#include <iostream>

namespace GraphParser {

// Forward declarations
class GraphNode;



// Custom exception class
class ParseException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Error parsing JSON";
    }
};

// Union for storing different types of data in a node
union NodeData {
    int intValue;
    double doubleValue;
    bool boolValue;
    QString* strValue;

    NodeData() : strValue(nullptr) {}
    ~NodeData() {
        if (strValue) {
            delete strValue;
        }
    }
};

// abstract base class
class JSONSerializable {
public:
    //virtual functions
    virtual void fromJSON(const QJsonObject& jsonObj) = 0;
    virtual QJsonObject toJSON() const = 0;
    virtual ~JSONSerializable() = default;
};

class GraphNode : public JSONSerializable {
public:
    GraphNode(const QString& id = "") : id(id), edges() {
        data.strValue = nullptr;
    }

    GraphNode(const GraphNode& other); // Copy constructor
    GraphNode& operator=(const GraphNode& other); // Assignment operator

    virtual ~GraphNode();

    void addEdge(std::shared_ptr<GraphNode> node);
    void setData(const NodeData& newData);

    const QString& getId() const;
    const NodeData& getData() const;
    const QVector<std::shared_ptr<GraphNode>>& getEdges() const;

    void fromJSON(const QJsonObject& jsonObj) override;
    QJsonObject toJSON() const override;

    friend std::ostream& operator<<(std::ostream& os, const GraphNode& node);

protected:
    QString id;
    NodeData data;
    QVector<std::shared_ptr<GraphNode>> edges;
    void copyData(const GraphNode& other);
};
//templates
// declaration
// template<typename T>
// class JSONParser {
// public:
//     static std::shared_ptr<T> parse(const QJsonObject& jsonObj);
// };

// specialization
// template<>
// class JSONParser<GraphNode> {
// public:
//     static std::shared_ptr<GraphNode> parse(const QJsonObject& jsonObj);
// };
} // namespace GraphParser

#endif // GRAPHNODE_H
