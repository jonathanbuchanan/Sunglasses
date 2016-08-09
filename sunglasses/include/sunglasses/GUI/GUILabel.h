// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUILABEL_H
#define GUILABEL_H

#include <sunglasses/GUI/GUIView.h>

#include <string>

namespace sunglasses {

/// A label in the GUI toolkit
class GUILabel : public GUIView {
public:
    std::string getText() const { return text; }
    void setText(std::string t) { text = t; }
private:
    /// The text of the label
    std::string text;
};

} // namespace

#endif
