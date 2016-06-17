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
