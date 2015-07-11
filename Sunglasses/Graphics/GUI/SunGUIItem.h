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
    
    vector<SunNodeSentAction> sentActions;
    
    GLFWwindow *window;
    
    SunGUIItem() {
        initializeDefaultPropertyAndFunctionMap();
        
        mesh.setUpGL();
    }
    
    void hide(SunNodeSentAction _action) {
        visible = false;
    }
    
    void show(SunNodeSentAction _action) {
        visible = true;
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
        SunNode::initializeDefaultPropertyAndFunctionMap();
        
        functionMap["render"] = bind(&SunGUIItem::render, this, std::placeholders::_1);
        functionMap["update"] = bind(&SunGUIItem::update, this, std::placeholders::_1);
        functionMap["hide"] = bind(&SunGUIItem::hide, this, std::placeholders::_1);
        functionMap["show"] = bind(&SunGUIItem::show, this, std::placeholders::_1);
        functionMap["toggleMouse"] = bind(&SunGUIItem::toggleMouse, this, std::placeholders::_1);
        functionMap["closeWindow"] = bind(&SunGUIItem::closeWindow, this, std::placeholders::_1);
    }
    
    map<string, GLboolean> activeTriggers(map<int, SunButtonState> _buttons, GLboolean _containsMouse) {
        map<string, GLboolean> triggers;
        
        triggers["click"] = false;
        triggers["escape"] = false;
        
        if (_buttons[GLFW_MOUSE_BUTTON_LEFT] == SunButtonStatePressedEdge && _containsMouse)
            triggers["click"] = true;
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
        highlighted = pointInItem(*(glm::vec2 *)_action.parameters["mousePosition"]);
        
        sendActions(activeTriggers(*(map<int, SunButtonState> *)_action.parameters["buttons"], highlighted));
    }
    
    void render(SunNodeSentAction _action) {
        if (visible)
            mesh.render(position, size, color, textured, highlightColor, highlighted, text, font, (SunTextRenderer *)_action.parameters["textRenderer"]);
    }
    
    void loadTexture() {
        mesh.loadTexture(texturePath);
    }
    
    GLboolean pointInItem(glm::vec2 _point) {
        if (_point.x >= position.x && _point.x <= position.x + size.x && _point.y <= position.y + size.y && _point.y >= position.y)
            return true;
        return false;
    }
    
private:
    
};

#endif
