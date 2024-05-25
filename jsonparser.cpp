#include "GraphNode.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <stdexcept>

using namespace GraphParser;

GraphNode::GraphNode(const GraphNode& other) {
    id = other.id;
    copyData(other);
    for (const auto& edge : other.edges) {
        edges.push_back(std::make_shared<GraphNode>(*edge));
    }
}

GraphNode& GraphNode::operator=(const GraphNode& other) {
    if (this != &other) {
        id = other.id;
        copyData(other);
        edges.clear();
        for (const auto& edge : other.edges) {
            edges.push_back(std::make_shared<GraphNode>(*edge));
        }
    }
    return *this;
}

GraphNode::~GraphNode() {
    if (data.strValue) {
        delete data.strValue;
    }
}

void GraphNode::addEdge(std::shared_ptr<GraphNode> node) {
    edges.push_back(node);
}

void GraphNode::setData(const NodeData& newData) {
    if (data.strValue) {
        delete data.strValue;
    }
    data = newData;
}

const QString& GraphNode::getId() const {
    return id;
}

const NodeData& GraphNode::getData() const {
    return data;
}

const QVector<std::shared_ptr<GraphNode>>& GraphNode::getEdges() const {
    return edges;
}

void GraphNode::fromJSON(const QJsonObject& jsonObj) {
    if (jsonObj.contains("id") && jsonObj["id"].isString()) {
        id = jsonObj["id"].toString();
    }
    if (jsonObj.contains("data")) {
        if (jsonObj["data"].isString()) {
            data.strValue = new QString(jsonObj["data"].toString());
        } else if (jsonObj["data"].isDouble()) {
            data.doubleValue = jsonObj["data"].toDouble();
        } else if (jsonObj["data"].isBool()) {
            data.boolValue = jsonObj["data"].toBool();
        }
    }
    if (jsonObj.contains("edges") && jsonObj["edges"].isArray()) {
        QJsonArray edgesArray = jsonObj["edges"].toArray();
        for (const auto& edge : edgesArray) {
            if (edge.isObject()) {
                auto node = JSONParser<GraphNode>::parse(edge.toObject());
                edges.push_back(node);
            }
        }
    }
}

QJsonObject GraphNode::toJSON() const {
    QJsonObject jsonObj;
    jsonObj["id"] = id;
    if (data.strValue) {
        jsonObj["data"] = *data.strValue;
    } else {
        // Handling other types of NodeData
        jsonObj["data"] = QJsonValue(); // Placeholder for other types
    }
    QJsonArray edgesArray;
    for (const auto& edge : edges) {
        edgesArray.append(edge->toJSON());
    }
    jsonObj["edges"] = edgesArray;
    return jsonObj;
}

std::ostream& operator<<(std::ostream& os, const GraphNode& node) {
    os << "GraphNode ID: " << node.id.toStdString() << "\nData: ";
    if (node.data.strValue) {
        os << node.data.strValue->toStdString();
    } else {
        os << "null";
    }
    os << "\nEdges: ";
    for (const auto& edge : node.edges) {
        os << edge->id.toStdString() << " ";
    }
    os << std::endl;
    return os;
}

void GraphNode::copyData(const GraphNode& other) {
    if (other.data.strValue) {
        data.strValue = new QString(*other.data.strValue);
    } else {
        data = other.data;
    }
}

template<>
std::shared_ptr<GraphNode> JSONParser<GraphNode>::parse(const QJsonObject& jsonObj) {
    auto node = std::make_shared<GraphNode>();
    node->fromJSON(jsonObj);
    return node;
}

template<typename T>
T JSONParser<T>::parse(const QJsonObject& jsonObj) {
    static_assert(sizeof(T) == 0, "Template specialization not provided for this type");
}
