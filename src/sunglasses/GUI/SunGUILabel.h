// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUILABEL_H
#define SUNGUILABEL_H

#include "SunGUIView.h"

#include <string>

/// A label in the GUI toolkit
class SunGUILabel : public SunGUIView {
public:
    std::string getText() const { return text; }
    void setText(std::string t) { text = t; }
private:
    /// The text of the label
    std::string text;
};

#endif
