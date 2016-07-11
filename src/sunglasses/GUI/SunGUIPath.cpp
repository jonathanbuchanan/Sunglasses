// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/SunGUIPath.h>

SunGUIFillPath SunGUIPath::fill() {
    std::vector<glm::ivec2> vertices = {};
    for (auto &operation : operators)
        operation->addGeometry(vertices);
    return SunGUIFillPath(vertices);
}

SunGUIPath::SunGUIPath(const std::vector<std::shared_ptr<const ISunGUIPathOperator>> &&_operators) :
    operators(_operators) {

}

namespace SunGUIPathOperator {
    PointAt::PointAt(glm::ivec2 point) : location(point) {

    }

    void PointAt::addGeometry(std::vector<glm::ivec2> &points) const {
        points.push_back(location);
    }

    LineTo::LineTo(glm::ivec2 point) : endpoint(point) {

    }

    void LineTo::addGeometry(std::vector<glm::ivec2> &points) const {
        points.push_back(endpoint);
    }

    Line::Line(glm::ivec2 _a, glm::ivec2 _b) : a(_a), b(_b) {

    }

    void Line::addGeometry(std::vector<glm::ivec2> &points) const {
        points.push_back(a);
        points.push_back(b);
    }
};

SunGUIPath rectangle(glm::ivec2 origin, glm::ivec2 size) {
    return SunGUIPath(std::vector<std::shared_ptr<const ISunGUIPathOperator>>{
        std::make_shared<SunGUIPathOperator::PointAt>(origin),
        std::make_shared<SunGUIPathOperator::PointAt>(origin + size.x),
        std::make_shared<SunGUIPathOperator::PointAt>(origin + size),
        std::make_shared<SunGUIPathOperator::PointAt>(origin + size.y)
    });
}

