#include "SunGUIMenu.h"

void SunGUIMenu::hide(SunNodeSentAction _action) {
    visible = false;
}

void SunGUIMenu::show(SunNodeSentAction _action) {
    visible = true;
}

void SunGUIMenu::toggleMouse(SunNodeSentAction _action) {
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SunGUIMenu::closeWindow(SunNodeSentAction _action) {
    glfwSetWindowShouldClose(window, true);
}

void SunGUIMenu::initializeDefaultPropertyAndFunctionMap() {
    SunNode::initializeDefaultPropertyAndFunctionMap();

    addToPropertyMap("visible", SunNodeProperty(&visible, SunNodePropertyTypeBool));

    addToFunctionMap("render", bind(&SunGUIMenu::render, this, std::placeholders::_1));
    addToFunctionMap("update", bind(&SunGUIMenu::update, this, std::placeholders::_1));
    addToFunctionMap("hide", bind(&SunGUIMenu::hide, this, std::placeholders::_1));
    addToFunctionMap("show", bind(&SunGUIMenu::show, this, std::placeholders::_1));
    addToFunctionMap("toggleMouse", bind(&SunGUIMenu::toggleMouse, this, std::placeholders::_1));
    addToFunctionMap("closeWindow", bind(&SunGUIMenu::closeWindow, this, std::placeholders::_1));
}

map<string, GLboolean> SunGUIMenu::activeTriggers(map<int, SunButtonState> _buttons) {
    map<string, GLboolean> triggers;

    triggers["escape"] = false;

    if (_buttons[GLFW_KEY_ESCAPE] == SunButtonStatePressedEdge)
        triggers["escape"] = true;

    return triggers;
}

void SunGUIMenu::sendActions(map<string, GLboolean> _activeTriggers) {
    for (int i = 0; i < sentActions.size(); ++i) {
        if (_activeTriggers[*(string *)sentActions[i].properties["trigger"]] == true) {
            sendAction(sentActions[i], (SunNode *)sentActions[i].properties["receiver"]);
        }
    }
}

void SunGUIMenu::update(SunNodeSentAction _action) {
    sendActions(activeTriggers(*(map<int, SunButtonState> *)_action.parameters["buttons"]));

    sendActionToAllSubNodes(_action);
}

void SunGUIMenu::render(SunNodeSentAction _action) {
    if (visible == true)
        sendActionToAllSubNodes(_action);
}