#pragma once

#include "Shape.h"

namespace Homework {

class Rectangle : public Shape {
public:
    Rectangle(const std::string& name, const Color& color, int orderInLayer)
        : Shape(name, color, orderInLayer) { }

    void setHeight(double height) {
        //implementation
    }

    void setWeight(double weight) {
        //implementation
    }
};

};
