// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef LABEL_H
#define LABEL_H

#include <sunglasses/GUI/View.h>

#include <string>

namespace sunglasses {
namespace GUI {

/// A label in the GUI toolkit
class Label : public View {
public:
    std::string getText() const { return text; }
    void setText(std::string t) { text = t; }
private:
    /// The text of the label
    std::string text;
};

} // namespace
} // namespace

#endif
