// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIPath.h"

namespace SunGUIPathOperator {
    PointAt::PointAt(glm::ivec2 point) : location(point) {

    }

    void PointAt::addGeometry(std::vector<glm::ivec2> &points) {
        points.push_back(location);
    }

    LineTo::LineTo(glm::ivec2 point) : endpoint(point) {

    }

    void LineTo::addGeometry(std::vector<glm::ivec2> &points) {
        points.push_back(endpoint);
    }

    Line::Line(glm::ivec2 _a, glm::ivec2 _b) : a(_a), b(_b) {

    }

    void Line::addGeometry(std::vector<glm::ivec2> &points) {
        points.push_back(a);
        points.push_back(b);
    }
};
