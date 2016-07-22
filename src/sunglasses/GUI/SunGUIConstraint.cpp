// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIConstraint.h"

SunGUIConstraintExpressionConstant::SunGUIConstraintExpressionConstant(int _constant) :
    constant(_constant) {

}

int SunGUIConstraintExpressionConstant::value() {
    return constant;
}





SunGUIConstraint::SunGUIConstraint(int _priority) : priority(_priority) {

}

SunGUIWidthConstraint::SunGUIWidthConstraint(SunGUIConstraintExpression *_expression, int _priority) :
    SunGUIConstraint(_priority), expression(_expression) {

}

void SunGUIWidthConstraint::adjustView(SunGUIView &view) {
    view.size.x = expression->value();
}
