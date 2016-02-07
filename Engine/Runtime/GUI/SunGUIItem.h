// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunGUIItem_h
#define Sunglasses_SunGUIItem_h

#include "SunNode.h"

#include "GUI/SunGUIAction.h"
#include "GUI/SunGUIItemMesh.h"

#include <map>

class SunGUIItem : public SunNode {
public:
    SunGUIItem();
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    
    void render(SunNodeSentAction _action);
    
    void button(SunNodeSentAction _action);
    
    void loadTexture();
    
    GLboolean pointInItem(glm::vec2 _point);
    
    inline string & getText() { return text; }
    inline void setText(string _text) { text = _text; } 
    
    inline string & getFont() { return font; }
    inline void setFont(string _font) { font = _font; }
    
    inline bool & getIsButton() { return isButton; }
    inline void setIsButton(bool _isButton) { isButton = _isButton; }
    
    inline glm::vec2 & getPosition() { return position; }
    inline void setPosition(glm::vec2 _position) { position = _position; }
    
    inline glm::vec2 & getSize() { return size; }
    inline void setSize(glm::vec2 _size) { size = _size; }
    
    inline glm::vec3 & getColor() { return color; }
    inline void setColor(glm::vec3 _color) { color = _color; }
    
    inline glm::vec3 & getHighlightColor() { return highlightColor; }
    inline void setHighlightColor(glm::vec3 _highlightColor) { highlightColor = _highlightColor; }
    
    inline GLboolean & getTextured() { return textured; }
    inline void setTextured(GLboolean _textured) { textured = _textured; }
    
    inline string & getTexturePath() { return texturePath; }
    inline void setTexturePath(string _texturePath) { texturePath = _texturePath; }
    
    inline GLboolean & getHighlighted() { return highlighted; }
    inline void setHighlighted(GLboolean _highlighted) { highlighted = _highlighted; }
    
    inline GLboolean & getVisible() { return visible; }
    inline void setVisible(GLboolean _visible) { visible = _visible; }
    
    inline GLFWwindow * getWindow() { return window; }
    inline void setWindow(GLFWwindow *_window) { window = _window; }
    
    inline void addActionForKey(SunGUIAction a, int k) { actions[k] = a; }
private:
    string text;

    string font;

    bool isButton;

    SunGUIItemMesh mesh;

    glm::vec2 position;
    glm::vec2 size;
    glm::vec3 color;
    glm::vec3 highlightColor;
    GLboolean textured;
    string texturePath;

    GLboolean highlighted;

    GLboolean visible = true;

    GLFWwindow *window;
    
    std::map<int, SunGUIAction> actions;
};

#endif
