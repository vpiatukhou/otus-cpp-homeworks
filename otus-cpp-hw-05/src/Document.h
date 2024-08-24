#pragma once

#include "Shape.h"
#include <memory>

namespace Homework {

/// @brief A document contains all shapes which were drawn.
class Document {
public:
    Document() = default;
    Document(const Document&) = delete;
    Document(Document&&) = delete;

    Document operator=(const Document&) = delete;
    Document operator=(Document&&) = delete;

    void setName(const std::string& name) {
        //implementation
    }

    void addShape(const std::shared_ptr<Shape>& shape) {
        //implementation
    }

    void deleteShape(const std::shared_ptr<Shape>& shape) {
        //implementation
    }

    std::shared_ptr<Shape> selectShape(double positionX, double positionY) {
        //implementation
        return nullptr;
    }
};

};
