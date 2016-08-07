// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIVIEW_H
#define SUNGUIVIEW_H

#include <glm/glm.hpp>

#include <sunglasses/GUI/SunGUIWindow.h>

#include <vector>

#include <rhea/simplex_solver.hpp>

class SunGUIViewController;
class SunGUIRenderer;

/// The state of a control
enum class SunGUIControlState {
    Normal,
    Highlighted,
    Selected
};

/// A view in the GUI toolkit
class SunGUIView {
friend SunGUIViewController;
public:
    /// An integer that is controlled by a variable in the simplex solver
    /**
     * This variable is guaranteed to be a stay constraint with a required strength.
     */
    struct ConstraintInt {
        /// Constructs it from an integer
        ConstraintInt(rhea::simplex_solver &_solver, int value);

        /// Assigns the variable from an integer
        void operator =(int value);

        /// Implicitly converts to an integer
        operator int();

        /// Implicitly converts to a linear expression
        operator rhea::linear_expression();

        /// The variable
        rhea::variable variable;
    private:
        /// The simplex solver (used to suggest new values when assigned)
        rhea::simplex_solver &solver;

        /// The stay constraint on the variable
        rhea::stay_constraint constraint;
    };

    /// A 2-vector that contains rhea variables, and can be implicitly converted to glm::ivec2
    struct vec2 {
        /// Constructs the vector from two values
        vec2(rhea::simplex_solver &_solver, int _x, int _y);

        /// Constructs the vector from glm::ivec2
        vec2(rhea::simplex_solver &_solver, glm::ivec2 vector);

        /// Assignment from glm::ivec2
        void operator =(glm::ivec2 vector);

        /// Implicit conversion to glm::ivec2
        operator glm::ivec2();

        /// The x variable
        ConstraintInt x;

        /// The y variable
        ConstraintInt y;
    };

    /// Constructs the view
    SunGUIView(glm::ivec2 _position,
        glm::ivec2 _size,
        glm::vec4 color,
        bool _visible = true);

    /// Updates all the sub-views and updates this view
    /**
     * @param parentPosition The absolute position of the parent view
     * @param info The info used to update the view
     */
    void updateTree(glm::ivec2 parentPosition, SunGUIUpdateInfo info);

    /// Draws all the sub-views and draws this view
    /**
     * @param parentPosition The absolute position of the parent view
     * @param renderer The object used to draw the view
     */
    virtual void drawTree(glm::ivec2 parentPosition, SunGUIRenderer &renderer);

    /// Adds a subview
    void addSubview(SunGUIView *subview);

    /// Various values that constraints can control
    enum struct ConstraintValue {
        Left,
        Right,
        Top,
        Bottom,
        CenterX,
        CenterY,
        Width,
        Height
    };

    /// Returns an expression for a constraint value
    rhea::linear_expression expressionForValue(ConstraintValue value);

    /// Returns an expression for a constraint value
    rhea::linear_expression operator[](ConstraintValue value);

    /// Adds a constraint concerning subviews and the bounding frame
    void addConstraint(rhea::constraint constraint);

    /// The position of the view (In pixels, not NDC)
    vec2 position;

    /// The size of the view (In pixels, not NDC)
    vec2 size;
protected:
    /// Updates the view
    virtual void update(glm::ivec2 parentPosition, SunGUIUpdateInfo info);

    /// Draws the view
    virtual void draw(glm::ivec2 parentPosition, SunGUIRenderer &renderer);

    /// The background color of the view
    glm::vec4 backgroundColor;

    /// The visibility of the view
    bool visible;

    /// The state of the control
    SunGUIControlState state;
private:
    /// The vector of sub-views
    std::vector<SunGUIView *> subviews;

    /// The constraint solver for the sub-views
    rhea::simplex_solver solver;
};

#endif
