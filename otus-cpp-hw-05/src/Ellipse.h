#pragma once

#include "Shape.h"

namespace Homework {

class Ellipse : public Shape {
public:
    Ellipse(const std::string& name, const Color& color, int orderInLayer)
        : Shape(name, color, orderInLayer) { }

    void setHalfRadiusX(double halfRadiusX) {
        //implementation
    }

    void setHalfRadiusY(double halfRadiusY) {
        //implementation
    }
};

};
