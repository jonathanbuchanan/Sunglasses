//
//  SunGUIItem.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 6/12/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef Sunglasses_SunGUIItem_h
#define Sunglasses_SunGUIItem_h

#include "SunNode.h"

#include "SunGUIItemMesh.h"

#include <map>

class SunGUIItem;

typedef void *SunGUIItemSentActionValue;

struct SunGUIItemSentAction {
    string trigger;
    string targetPath;
    string action;
    string targetProperty;
    string valueType;
    SunGUIItemSentActionValue value;
    
    SunGUIItem *receiver;
};

typedef void (SunGUIItem::*SunGUIItemFunctionPointer)(SunGUIItemSentAction);
typedef void *SunGUIItemPropertyPointer;

class SunGUIItem : public SunNode {
public:
    string name;
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
    
    map<string, SunGUIItemFunctionPointer> functions;
    map<string, SunGUIItemPropertyPointer> properties;
    
    vector<SunGUIItemSentAction> sentActions;
    
    GLFWwindow *window;
    
    SunGUIItem() {
        setUpReceivedFunctionsAndProperties();
        
        mesh.setUpGL();
    }
    
    void hide(SunGUIItemSentAction _action) {
        
    }
    
    void changeValue(SunGUIItemSentAction _action) {
        string targetProperty = _action.targetProperty;
        string valueType = _action.valueType;
        
        if (valueType == "vec3") {
            *((glm::vec3 *)properties[targetProperty]) = *(glm::vec3 *)_action.value;
        }
    }
    
    void toggleBool(SunGUIItemSentAction _action) {
        
    }
    
    void closeWindow(SunGUIItemSentAction _action) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    void setUpReceivedFunctionsAndProperties() {
        functions["hide"] = &SunGUIItem::hide;
        functions["changeValue"] = &SunGUIItem::changeValue;
        functions["toggleBool"] = &SunGUIItem::toggleBool;
        functions["closeWindow"] = &SunGUIItem::closeWindow;
        
        properties["color"] = &color;
    }
    
    void receiveAction(SunGUIItemSentAction _action) {
        SunGUIItemFunctionPointer pointer = functions[_action.action];
        (this->*pointer)(_action);
    }
    
    void loadTexture() {
        mesh.loadTexture(texturePath);
    }
    
    void sendActions(map<string, bool> _triggers) {
        for (int i = 0; i < sentActions.size(); i++) {
            if (_triggers[sentActions[i].trigger] == true)
                sentActions[i].receiver->receiveAction(sentActions[i]);
        }
    }
    
    map<string, bool> activeTriggers(map<int, SunButtonState> _buttons, GLboolean _containsMouse) {
        map<string, bool> triggers;
        
        triggers["click"] = false;
        triggers["escape"] = false;
        
        if (_buttons[GLFW_MOUSE_BUTTON_LEFT] == SunButtonStatePressedEdge && _containsMouse)
            triggers["click"] = true;
        if (_buttons[GLFW_KEY_ESCAPE] == SunButtonStatePressedEdge)
            triggers["escape"] = true;
            
        return triggers;
    }
    
    void update(map<int, SunButtonState> _buttons, GLdouble _mouseXPosition, GLdouble _mouseYPosition) {
        highlighted = pointInItem(glm::vec2(_mouseXPosition, _mouseYPosition));
        
        sendActions(activeTriggers(_buttons, highlighted));
    }
    
    void render(SunTextRenderer *_renderer) {
        if (visible)
            mesh.render(position, size, color, textured, highlightColor, highlighted, text, font, _renderer);
    }
    
    GLboolean pointInItem(glm::vec2 _point) {
        if (_point.x >= position.x && _point.x <= position.x + size.x && _point.y <= position.y + size.y && _point.y >= position.y)
            return true;
        return false;
    }
    
private:
    
};

#endif
