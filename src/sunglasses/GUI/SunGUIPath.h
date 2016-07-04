// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIPATH_H
#define SUNGUIPATH_H

#include <functional>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include <sunglasses/GUI/SunGUIRendering.h>

/// The interface for a path operator
class ISunGUIPathOperator {
public:
    /// The method used to add geometry to the path
    virtual void addGeometry(std::vector<glm::ivec2> &points) = 0;
};

/// A path in the GUI system.
/**
 * Can contain multiple 'operators', which are objects that
 * tell the path how to generate a fillable or strokable object.
 */
class SunGUIPath {
public:
    /// Constructs the path with a set of operators
    template<typename... T>
    SunGUIPath(const T &... _operators) :
        operators{std::ref((const ISunGUIPathOperator &)(_operators))...} {

    }

    /// Returns a fillable object
    //SunGUIFill fill() {
        //return SunGUIFill();
    //}
private:
    /// The set of operators
    std::vector<std::reference_wrapper<const ISunGUIPathOperator>> operators;
};

namespace SunGUIPathOperator {
    /// Generates a single point at the specified coordinates.
    class PointAt : ISunGUIPathOperator {
    public:
        /// Constructs the operator with the location of the point
        PointAt(glm::ivec2 point);

        /// Adds a single point to the path's vertices
        virtual void addGeometry(std::vector<glm::ivec2> &points);
    private:
        /// The location of the point
        glm::ivec2 location;
    };

    /// Generates a line from the last used point to the specified point.
    class LineTo {
    public:
        /// Constructs the operater with the second endpoint
        LineTo(glm::ivec2 point);

        /// Adds the endpoint to the path's vertices
        virtual void addGeometry(std::vector<glm::ivec2> &points);
    private:
        /// The location of the second endpoint
        glm::ivec2 endpoint;
    };

    /// Generates a line from the two endpoints
    /**
     * @warn This will not be connected to the previous point,
     * even if the first endpoint coincides with it.
     */
    class Line {
    public:
        /// Constructs the operater with the two endpoints
        Line(glm::ivec2 _a, glm::ivec2 _b);

        /// Adds the two endpoints to the path's vertices
        virtual void addGeometry(std::vector<glm::ivec2> &points);
    private:
        /// The two endpoints of the line
        glm::ivec2 a, b;
    };

    class ArcTo {

    };

    class Arc {

    };

    class BezierCurveTo {

    };

    class BezierCurve {

    };
}

#endif
