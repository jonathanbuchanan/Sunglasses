//
//  SunGUIMenu.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 6/12/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef Sunglasses_SunGUIMenu_h
#define Sunglasses_SunGUIMenu_h

#include <vector>

#include "SunGUIItem.h"

class SunGUIMenu;

typedef void *SunGUIMenuSentActionValue;

struct SunGUIMenuSentAction {
    string trigger;
    string targetPath;
    string action;
    string targetProperty;
    string valueType;
    SunGUIMenuSentActionValue value;
    
    SunGUIMenu *receiver;
};

typedef void (SunGUIMenu::*SunGUIMenuFunctionPointer)(SunGUIMenuSentAction);
typedef void *SunGUIMenuPropertyPointer;

class SunGUIMenu : public SunNode {
public:
    vector<SunGUIItem *> items;
    
    string name;
    GLboolean visible;
    
    map<string, SunGUIMenuFunctionPointer> functions;
    map<string, SunGUIMenuPropertyPointer> properties;
    
    vector<SunGUIMenuSentAction> sentActions;
    
    GLFWwindow *window;
    
    SunGUIMenu() {
        setUpReceivedFunctionsAndProperties();
    }
    
    void hide(SunGUIMenuSentAction _action) {
        
    }
    
    void changeValue(SunGUIMenuSentAction _action) {
        string targetProperty = _action.targetProperty;
        string valueType = _action.valueType;
        
        if (valueType == "vec3") {
            *((glm::vec3 *)properties[targetProperty]) = *(glm::vec3 *)_action.value;
        }
    }
    
    void toggleBool(SunGUIMenuSentAction _action) {
        string targetProperty = _action.targetProperty;
        
        *((GLboolean *)properties[targetProperty]) = !*((GLboolean *)properties[targetProperty]);
    }
    
    void toggleMouse(SunGUIMenuSentAction _action) {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
    void setUpReceivedFunctionsAndProperties() {
        functions["hide"] = &SunGUIMenu::hide;
        functions["changeValue"] = &SunGUIMenu::changeValue;
        functions["toggleBool"] = &SunGUIMenu::toggleBool;
        functions["toggleMouse"] = &SunGUIMenu::toggleMouse;
        
        properties["visible"] = &visible;
    }
    
    void receiveAction(SunGUIMenuSentAction _action) {
        SunGUIMenuFunctionPointer pointer = functions[_action.action];
        (this->*pointer)(_action);
    }
    
    void leftMouseButtonActions() {
        for (int i = 0; i < sentActions.size(); i++) {
            if (sentActions[i].trigger == "click") {
                sentActions[i].receiver->receiveAction(sentActions[i]);
            }
        }
    }
    
    void sendActions(map<string, bool> _triggers) {
        for (int i = 0; i < sentActions.size(); i++) {
            if (_triggers[sentActions[i].trigger] == true)
                sentActions[i].receiver->receiveAction(sentActions[i]);
        }
    }
    
    map<string, bool> activeTriggers(map<int, SunButtonState> _buttons) {
        map<string, bool> triggers;
        
        triggers["click"] = false;
        triggers["escape"] = false;
        
        if (_buttons[GLFW_MOUSE_BUTTON_LEFT] == SunButtonStatePressedEdge)
            triggers["click"] = true;
        if (_buttons[GLFW_KEY_ESCAPE] == SunButtonStatePressedEdge)
            triggers["escape"] = true;
        return triggers;
    }
    
    void update(map<int, SunButtonState> _buttons, GLdouble _mouseXPosition, GLdouble _mouseYPosition) {
        sendActions(activeTriggers(_buttons));
        
        for (int i = 0; i < items.size(); i++) {
            items[i]->update(_buttons, _mouseXPosition, _mouseYPosition);
        }
    }
    
    void render(SunTextRenderer *_renderer) {
        if (visible == true) {
            for (int i = 0; i < items.size(); i++) {
                items[i]->render(_renderer);
            }
        }
    }
    
private:
    
};

#endif
