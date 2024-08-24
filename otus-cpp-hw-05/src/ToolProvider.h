#pragma once

#include "Document.h"
#include "Shape.h"

#include <cstddef>
#include <string>
#include <memory>

namespace Homework {

/// @brief Provides tools for creation of different Shapes within the current Document.
class ToolProvider {
private:
    std::shared_ptr<Shape> selectedShape = nullptr;
    std::shared_ptr<Document> document;
public:
    ToolProvider(const std::shared_ptr<Document>& document);

    void createEllipse();
    void createRectangle();

    void addSelectedShapeToDocument(double positionX, double positionY);
    void selectShape(double positionX, double positionY);
    void deleteSelectedShape();
};

};
