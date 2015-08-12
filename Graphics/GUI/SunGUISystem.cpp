#include "SunGUISystem.h"

SunGUISystem::SunGUISystem(const char* filepath, GLFWwindow* _window, SunNode* _rootNode) {
    window = _window;
    setRootNode(_rootNode);

    initializeDefaultPropertyAndFunctionMap();

    pugi::xml_document document;
    document.load_file(filepath);

    pugi::xml_node system = document.child("GUISystem");

    for (pugi::xml_attribute attribute = system.first_attribute(); attribute; attribute = attribute.next_attribute()) {
        if (strcmp(attribute.name(), "name") == 0) {
            setName(attribute.value());
        }
    }

    processXMLGUISystemNode(system);
}

SunGUISystem::initializeDefaultPropertyAndFunctionMap() {
    SunNode::initializeDefaultPropertyAndFunctionMap();

    // Add the "render" function to the function map
    addToFunctionMap("update", bind(&SunGUISystem::update, this, std::placeholders::_1));
    addToFunctionMap("render", bind(&SunGUISystem::render, this, std::placeholders::_1));
}

void SunGUISystem::update(SunNodeSentAction _action) {
    // Loop through the sub-objects and force them to update
    sendActionToAllSubNodes(_action);
}

void SunGUISystem::render(SunNodeSentAction _action) {
    glEnable(GL_BLEND);

    // Loop through the sub-objects and force them to render
    sendActionToAllSubNodes(_action);

    glDisable(GL_BLEND);
}

void SunGUISystem::loadFonts(SunTextRenderer* _textRenderer) {
    for (int i = 0; i < fonts.size(); i++) {
        _textRenderer->loadFont(fonts[i].file, fonts[i].name);
    }

    fontsLoaded = true;
}