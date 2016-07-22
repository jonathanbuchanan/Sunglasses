// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUICONSTRAINT_H
#define SUNGUICONSTRAINT_H

#include <memory>

#include <sunglasses/GUI/SunGUIView.h>

/// An expression used to control the value of a constraint
class SunGUIConstraintExpression {
public:
    /// The value of the expression
    virtual int value() = 0;
private:

};



/// An expression that holds a constant value
class SunGUIConstraintExpressionConstant : public SunGUIConstraintExpression {
public:
    /// Constructs the expression with a constant value
    SunGUIConstraintExpressionConstant(int constant);

    /// Returns the value of the constant
    virtual int value();
private:
    /// The value of the constant
    int constant;
};





/// An abstract class representing a constraint to a GUI view
class SunGUIConstraint {
public:
    /// Constructs the constraint with a priority
    SunGUIConstraint(int _priority);

    /// Adjusts the view to satisfy the constraint
    virtual void adjustView(SunGUIView &view) = 0;
private:
    /// The priority of the constraint
    /**
     * When two constraints are conflicting, the one with
     * greater priority is satisfied. If two conflicting constraints
     * have equal priority, none of them will be satisfied.
     */
    int priority;
};



/// A constraint that controls the width of a view
class SunGUIWidthConstraint : public SunGUIConstraint {
public:
    /// Constructs the constraint with an expression and a priority
    SunGUIWidthConstraint(SunGUIConstraintExpression *_expression, int _priority);

    /// Adjusts the width of the view to match the value of the expression
    virtual void adjustView(SunGUIView &view);
private:
    /// The expression controlling the width
    std::unique_ptr<SunGUIConstraintExpression> expression;
};






#endif
