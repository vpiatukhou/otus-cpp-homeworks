#pragma once

#include "Color.h"
#include <string>

namespace Homework {

/// @brief A base class for all objects which can be drawn.
class Shape {
public:
    virtual ~Shape() = default;

    void setName(const std::string& name) {
        //implementation
    }

    void setColor(const Color& color) {
        //implementation
    }

    void setOrderInLayer(int orderInLayer) {
        //implementation
    }

    void setPositionX(double positionX) {
        //implementation
    }

    void setPositionY(double positionY) {
        //implementation
    }
protected:
    Shape(const std::string& name, const Color& color, int orderInLayer) {
        //implementation
    }
};

};
