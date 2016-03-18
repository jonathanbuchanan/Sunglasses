// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunGUIItem_h
#define Sunglasses_SunGUIItem_h

class SunScript;
class SunGUIMenu;

#include "../Core/SunNode.h"

#include "SunGUIItemMesh.h"

#include <map>

class SunGUIItem : public SunNode {
public:
    SunGUIItem();

    virtual void init();

    void render(SunAction action);

    void button(SunAction action);

    void loadTexture();

    bool pointInItem(glm::vec2 _point);
    bool cursorInItem();

    string & getText() { return text; }
    void setText(string _text) { text = _text; }

    string & getFont() { return font; }
    void setFont(string _font) { font = _font; }

    bool & getIsButton() { return isButton; }
    void setIsButton(bool _isButton) { isButton = _isButton; }

    glm::vec2 & getPosition() { return position; }
    void setPosition(glm::vec2 _position) { position = _position; }

    glm::vec2 & getSize() { return size; }
    void setSize(glm::vec2 _size) { size = _size; }

    glm::vec3 & getColor() { return color; }
    void setColor(glm::vec3 _color) { color = _color; }

    glm::vec3 & getHighlightColor() { return highlightColor; }
    void setHighlightColor(glm::vec3 _highlightColor) { highlightColor = _highlightColor; }

    GLboolean & getTextured() { return textured; }
    void setTextured(GLboolean _textured) { textured = _textured; }

    string & getTexturePath() { return texturePath; }
    void setTexturePath(string _texturePath) { texturePath = _texturePath; }

    GLboolean & getHighlighted() { return highlighted; }
    void setHighlighted(GLboolean _highlighted) { highlighted = _highlighted; }

    GLboolean & getVisible() { return visible; }
    void setVisible(GLboolean _visible) { visible = _visible; }

    void setScript(SunScript *s) { script = s; }
    void setScript(SunGUIMenu *m);

    void addMouseActionForTrigger(int trigger, std::string action) { mouseActions[trigger] = action; }
private:
    string text;

    string font;

    bool isButton;

    SunGUIItemMesh mesh;

    glm::vec2 position;
    glm::vec2 size;
    glm::vec3 color;
    glm::vec3 highlightColor;
    GLboolean textured = false;
    string texturePath;

    GLboolean highlighted = false;

    GLboolean visible = true;

    SunScript *script;

    std::map<int, std::string> mouseActions;
};

#endif
