// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunScene.h"

SunScene::SunScene() { 
    //setRootNode(this);

    // Initialize the property map
    initializeDefaultPropertyAndFunctionMap();
}

SunScene::SunScene(const char *filepath, GLFWwindow *_window) { 
    //setRootNode(this);

    // Set the window
    window = _window;

    // Initialize the property map
    initializeDefaultPropertyAndFunctionMap();

    rootRenderableNode = new SunObject();
    rootRenderableNode->setName("RootRenderableNode");

	SunAction playAction("play"); 
    
    if (autoplay)
        sendAction(playAction, music);
    
    // Load Point Lights
	SunAction pointLightAction("loadPointLights");
	pointLightAction.setRecursive(true); 
    
    sendAction(pointLightAction, renderer.getRootRenderNode());
}

void SunScene::initializeDefaultPropertyAndFunctionMap() {
    //SunObject::initializeDefaultPropertyAndFunctionMap();

    //setType("scene");

    //addToPropertyMap("doCameraInput", SunNodeProperty(&doCameraInput, SunNodePropertyTypeBool));

	//addAction("render", &SunScene::render);

	addAction("renderGUISystem", &SunScene::renderGUISystem);
	addAction("passPerFrameUniforms", &SunScene::passPerFrameUniformsAction);
	addAction("initializeShadowMapRenderer", &SunScene::initializeShadowMapRenderer); 
}

void SunScene::initializeShadowMapRenderer(SunAction action) {
    // Renderer
    SunPointShadowMapRenderingNode *renderer = (SunPointShadowMapRenderingNode *)action.getParameter("renderer");
    
    // Loop through shadow point lights and add to list
    for (int i = 0; i < shadowPointLights.size(); i++) {
        renderer->addLightToLights(shadowPointLights[i]);
    }
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
    sendAction(action, rootRenderableNode);
}

void SunScene::render(SunAction action) {
    map<string, SunShader> _shaders = *(map<string, SunShader> *)action.getParameter("shaderMap");
    GLfloat _deltaTime = *(GLfloat *)action.getParameter("deltaTime");
    string POVtype = *(string *)action.getParameter("POVtype");
    string POV = *(string *)action.getParameter("POV");
    vector<SunShaderUniformObject> uniforms;
    if (action.parameterExists("uniforms")) {
        uniforms = *(vector<SunShaderUniformObject> *)action.getParameter("uniforms");
    }

    // Force sub-objects to render
    
    for (SunShaderMapIterator iterator = _shaders.begin(); iterator != _shaders.end(); iterator++) {
		SunAction renderAction("render");
		renderAction.addParameter("shader", &iterator->second);

        if (iterator->first == "scene_solid")
            action.addParameter("renderType", new int(SunMeshRenderTypeSolid));
        else if (iterator->first == "scene_textured")
            action.addParameter("renderType", new int(SunMeshRenderTypeTextured));
        else if (iterator->first == "scene_all")
            action.addParameter("renderType", new int(SunMeshRenderTypeAll));
		action.addParameter("deltaTime", &_deltaTime);
		action.setRecursive(true);
        
        iterator->second.use();
            
        for (int i = 0; i < uniforms.size(); i++)
            uniforms[i].passUniform(&iterator->second);
        
        // Pass POV Uniforms
        if (POVtype == "camera") {
            camera.passPerFrameUniforms(iterator->second);
        } else if (POVtype == "light") {
        
        }
        
        passPerFrameUniforms(iterator->second);
        sendAction(action, rootRenderableNode);
    }
	
	if (action.parameterExists("uniforms")) {
    	uniforms = *(vector<SunShaderUniformObject> *)action.getParameter("uniforms");
    }
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

    sendAction(action, rootRenderableNode);
}

void SunScene::passPerFrameUniforms(SunShader _shader, vector<SunNodeSentActionCondition> _conditions) {
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
}

void SunScene::passPerFrameUniformsAction(SunAction action) {    
    SunShader _shader = *(SunShader *)action.getParameter("shader");
    vector<SunNodeSentActionCondition> _conditions = *(vector<SunNodeSentActionCondition> *)action.getParameter("conditions");
    
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

    sendAction(updateAction, rootRenderableNode);
}

