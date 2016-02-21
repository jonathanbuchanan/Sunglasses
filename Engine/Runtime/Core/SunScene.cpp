// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunScene.h"

SunScene::SunScene() { 
    
}

SunScene::SunScene(const char *filepath, GLFWwindow *_window) { 
    //setRootNode(this);

    // Set the window
    window = _window;

	SunAction playAction("play"); 
    
    if (autoplay)
        sendAction(playAction, music);
    
    // Load Point Lights
	SunAction pointLightAction("loadPointLights");
	pointLightAction.setRecursive(true); 
    
    sendAction(pointLightAction, renderer.getRootRenderNode());
}

void SunScene::init() { 
	addAction("renderGUISystem", &SunScene::renderGUISystem);
	addAction("passPerFrameUniforms", &SunScene::passPerFrameUniformsAction); 
} 

void SunScene::cycle(map<int, SunButtonState> _buttons, GLfloat _deltaTime) {
    physicsSimulator.cycle(_deltaTime);
    update(_buttons);
    renderer.render(_deltaTime);
}

void SunScene::update(map<int, SunButtonState> _buttons) {
    // Get the position of the mouse
    GLdouble xPosition, yPosition;
    glfwGetCursorPos(window, &xPosition, &yPosition);

    // Map Cursor Position to NDC
    GLdouble normalizedXPosition = (xPosition - 400) / 400;
    GLdouble normalizedYPosition = -(yPosition - 300) / 300;

    glm::vec2 *mousePosition = new glm::vec2(normalizedXPosition, normalizedYPosition);

	SunAction action("update");
	action.addParameter("mousePosition", mousePosition);
	action.addParameter("buttons", &_buttons);
        
    // Force sub-objects to update
    //sendAction(action, GUIsystem);
    //SunObject::update(action);
    
    action.setRecursive(true);
    sendAction(action, root);
} 

void SunScene::renderGUISystem(SunAction action) {
	SunAction GUIAction("render");
    //GUIAction.parameters["textRenderer"] = &textRenderer;
    
    //sendAction(GUIAction, GUIsystem);
}

void SunScene::passPerFrameUniforms(SunShader _shader) {
    glUniform1i(_shader.getUniformLocation("pointLightCount"), pointLightCount);
	glUniform1i(_shader.getUniformLocation("shadowPointLightCount"), shadowPointLightCount);
	glUniform1i(_shader.getUniformLocation("directionalLightCount"), directionalLightCount);
	glUniform1i(_shader.getUniformLocation("shadowDirectionalLightCount"), shadowDirectionalLightCount);
    
    listener.setPositionAndDirection();

	SunAction action("passPerFrameUniforms");
	action.addParameter("shader", &_shader);
	action.setRecursive(true);

    sendAction(action, root);
}

/*void SunScene::passPerFrameUniforms(SunShader _shader, vector<SunNodeSentActionCondition> _conditions) {
    glUniform1i(_shader.getUniformLocation("pointLightCount"), pointLightCount);
	glUniform1i(_shader.getUniformLocation("shadowPointLightCount"), shadowPointLightCount);
	glUniform1i(_shader.getUniformLocation("directionalLightCount"), directionalLightCount);
	glUniform1i(_shader.getUniformLocation("shadowDirectionalLightCount"), shadowDirectionalLightCount);
    
    camera.passPerFrameUniforms(_shader);

	SunAction action("passPerFrameUniforms");
	action.addParameter("shader", &_shader);
	//action.conditions
	action.setRecursive(true); 

    sendAction(action, rootRenderableNode);
}*/

void SunScene::passPerFrameUniformsAction(SunAction action) {    
    SunShader _shader = *(SunShader *)action.getParameter("shader");
    //vector<SunNodeSentActionCondition> _conditions = *(vector<SunNodeSentActionCondition> *)action.getParameter("conditions");
    
    glUniform1i(_shader.getUniformLocation("pointLightCount"), pointLightCount);
	glUniform1i(_shader.getUniformLocation("shadowPointLightCount"), shadowPointLightCount);
	glUniform1i(_shader.getUniformLocation("directionalLightCount"), directionalLightCount);
	glUniform1i(_shader.getUniformLocation("shadowDirectionalLightCount"), shadowDirectionalLightCount);
    
    camera.passPerFrameUniforms(_shader);

	SunAction updateAction("update");
	updateAction.addParameter("shader", &_shader);
	updateAction.addParameter("usedTextureUnits", action.getParameter("usedTextureUnits"));
	//updateAction.conditions
	updateAction.setRecursive(true);

    sendAction(updateAction, root);
} 
