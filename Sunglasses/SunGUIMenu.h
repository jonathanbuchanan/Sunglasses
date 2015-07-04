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

class SunGUIMenu : public SunNode {
public:
    string name;
    GLboolean visible;
    
    vector<SunNodeSentAction> sentActions;
    
    GLFWwindow *window;
    
    SunGUIMenu() {
        initializeDefaultPropertyAndFunctionMap();
    }
    
    void hide(SunNodeSentAction _action) {
        visible = false;
    }
    
    void show(SunNodeSentAction _action) {
        visible = true;
    }
    
    void changeValue(SunNodeSentAction _action) {
        string targetProperty = *(string *)_action.parameters["targetProperty"];
        
        if (propertyMap.find(targetProperty) != propertyMap.end()) {
            if (propertyMap[targetProperty].type == SunNodePropertyTypeVec3) {
                *((glm::vec3 *)propertyMap[targetProperty].pointer) = *((glm::vec3 *)_action.parameters["targetValuePointer"]);
            }
        }
    }
    
    void toggleBool(SunNodeSentAction _action) {
        string targetProperty = *(string *)_action.parameters["targetProperty"];
        
        if (propertyMap.find(targetProperty) != propertyMap.end()) {
            if (propertyMap[targetProperty].type == SunNodePropertyTypeBool)
                *((GLboolean *)propertyMap[targetProperty].pointer) = !*((GLboolean *)propertyMap[targetProperty].pointer);
        }
    }
    
    void toggleMouse(SunNodeSentAction _action) {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
    void closeWindow(SunNodeSentAction _action) {
        glfwSetWindowShouldClose(window, true);
    }
    
    void initializeDefaultPropertyAndFunctionMap() {
        propertyMap["visible"] = SunNodeProperty(&visible, SunNodePropertyTypeBool);
        
        functionMap["render"] = bind(&SunGUIMenu::render, this, std::placeholders::_1);
        functionMap["update"] = bind(&SunGUIMenu::update, this, std::placeholders::_1);
        functionMap["hide"] = bind(&SunGUIMenu::hide, this, std::placeholders::_1);
        functionMap["show"] = bind(&SunGUIMenu::show, this, std::placeholders::_1);
        functionMap["changeValue"] = bind(&SunGUIMenu::changeValue, this, std::placeholders::_1);
        functionMap["toggleBool"] = bind(&SunGUIMenu::toggleBool, this, std::placeholders::_1);
        functionMap["toggleMouse"] = bind(&SunGUIMenu::toggleMouse, this, std::placeholders::_1);
        functionMap["closeWindow"] = bind(&SunGUIMenu::closeWindow, this, std::placeholders::_1);
    }
    
    map<string, GLboolean> activeTriggers(map<int, SunButtonState> _buttons) {
        map<string, GLboolean> triggers;
        
        triggers["escape"] = false;
        
        if (_buttons[GLFW_KEY_ESCAPE] == SunButtonStatePressedEdge)
            triggers["escape"] = true;
        
        return triggers;
    }
    
    void sendActions(map<string, GLboolean> _activeTriggers) {
        for (int i = 0; i < sentActions.size(); ++i) {
            if (_activeTriggers[*(string *)sentActions[i].properties["trigger"]] == true) {
                sendAction(sentActions[i], (SunNode *)sentActions[i].properties["receiver"]);
            }
        }
    }
    
    void update(SunNodeSentAction _action) {
        sendActions(activeTriggers(*(map<int, SunButtonState> *)_action.parameters["buttons"]));
        
        sendActionToAllSubNodes(_action);
    }
    
    void render(SunNodeSentAction _action) {
        if (visible == true)
            sendActionToAllSubNodes(_action);
    }
    
private:
    
};

#endif
