#include "SunScene.h"

SunScene::SunScene() {
    // Normalize all physical properties
    setPosition(glm::vec3(0, 0, 0));
    setRotation(glm::vec3(0, 0, 0));
    setScale(glm::vec3(1.0, 1.0, 1.0));
    setRootNode(this);

    // Initialize the property map
    initializeDefaultPropertyAndFunctionMap();
}

SunScene::SunScene(const char *filepath, GLFWwindow *_window) {
    // Normalize all physical properties
    setPosition(glm::vec3(0, 0, 0));
    setRotation(glm::vec3(0, 0, 0));
    setScale(glm::vec3(1.0, 1.0, 1.0));
    setRootNode(this);

    // Set the window
    window = _window;

    // Initialize the property map
    initializeDefaultPropertyAndFunctionMap();

    // Set up the XML Parsing
    pugi::xml_document document;
    document.load_file(filepath);

    pugi::xml_node scene = document.child("scene");

    for (pugi::xml_attribute attribute = scene.first_attribute(); attribute; attribute = attribute.next_attribute()) {
        if (strcmp(attribute.name(), "name") == 0) {
            setName(attribute.value());
        } else if (strcmp(attribute.name(), "GUISystem") == 0) {
            GUIsystem = new SunGUISystem(attribute.value(), window, this);
            GUIsystem->setRootNode(this);
        }
    }

    textRenderer = SunTextRenderer();
    textRenderer.initialize();

    rootRenderableNode = new SunObject();
    rootRenderableNode->setName("RootRenderableNode");
    addSubNode(rootRenderableNode);

    // Process the XML scene node
    processXMLSceneNode(scene);

    GUIsystem->loadFonts(&textRenderer);

    GUIsystem->mapSentActionTargets();

    SunNodeSentAction action;
    action.action = "play";

    if (autoplay)
        sendAction(action, music);
    
    // Load Point Lights
    SunNodeSentAction pointLightAction;
    pointLightAction.action = "loadPointLights";
    pointLightAction.recursive = true;
    
    sendAction(pointLightAction, renderer.getRootRenderNode());
}

void SunScene::initializeDefaultPropertyAndFunctionMap() {
    SunObject::initializeDefaultPropertyAndFunctionMap();

    setType("scene");

    addToPropertyMap("doCameraInput", SunNodeProperty(&doCameraInput, SunNodePropertyTypeBool));

    addToFunctionMap("render", bind(&SunScene::render, this, std::placeholders::_1));
    addToFunctionMap("renderGUISystem", bind(&SunScene::renderGUISystem, this, std::placeholders::_1));
    addToFunctionMap("passPerFrameUniforms", bind(&SunScene::passPerFrameUniformsAction, this, std::placeholders::_1));
    addToFunctionMap("initializeShadowMapRenderer", bind(&SunScene::initializeShadowMapRenderer, this, std::placeholders::_1));
}

void SunScene::initializeShadowMapRenderer(SunNodeSentAction _action) {
	// Renderer
	SunShadowMapRenderingNode *renderer = (SunShadowMapRenderingNode *)_action.parameters["renderer"];
	
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

    SunNodeSentAction action;
    action.action = "update";
    action.parameters["mousePosition"] = mousePosition;
    action.parameters["buttons"] = &_buttons;

    // Force sub-objects to update
    sendAction(action, GUIsystem);
    SunObject::update(action);
    
    action.recursive = true;
    sendAction(action, rootRenderableNode);
}

void SunScene::render(SunNodeSentAction _action) {
    map<string, SunShader> _shaders = *(map<string, SunShader> *)_action.parameters["shaderMap"];
    GLfloat _deltaTime = *(GLfloat *)_action.parameters["deltaTime"];
    string POVtype = *(string *)_action.parameters["POVtype"];
    string POV = *(string *)_action.parameters["POV"];
    vector<SunShaderUniformObject> uniforms;
    if (_action.parameters.find("uniforms") != _action.parameters.end()) {
    	uniforms = *(vector<SunShaderUniformObject> *)_action.parameters["uniforms"];
    }

    // Force sub-objects to render
	
	for (SunShaderMapIterator iterator = _shaders.begin(); iterator != _shaders.end(); iterator++) {
		SunNodeSentAction action;
		action.action = "render";
		action.parameters["shader"] = &iterator->second;
		if (iterator->first == "scene_solid")
			action.parameters["renderType"] = new int(SunMeshRenderTypeSolid);
		else if (iterator->first == "scene_textured")
			action.parameters["renderType"] = new int(SunMeshRenderTypeTextured);
		else if (iterator->first == "scene_all")
			action.parameters["renderType"] = new int(SunMeshRenderTypeAll);
		action.parameters["deltaTime"] = &_deltaTime;
		action.recursive = true;
		
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
	
	if (_action.parameters.find("uniforms") != _action.parameters.end()) {
    	uniforms = *(vector<SunShaderUniformObject> *)_action.parameters["uniforms"];
    }
}

void SunScene::renderGUISystem(SunNodeSentAction _action) {
    SunNodeSentAction GUIAction;
    GUIAction.action = "render";
    GUIAction.parameters["textRenderer"] = &textRenderer;
    
    sendAction(GUIAction, GUIsystem);
}

void SunScene::passPerFrameUniforms(SunShader _shader) {
    glUniform1i(_shader.getUniformLocation("pointLightCount"), pointLightCount);
	glUniform1i(_shader.getUniformLocation("shadowPointLightCount"), shadowPointLightCount);
    
    listener.setPositionAndDirection();

    SunNodeSentAction action;
    action.action = "passPerFrameUniforms";
    action.parameters["shader"] = &_shader;
    action.recursive = true;

    sendAction(action, rootRenderableNode);
}

void SunScene::passPerFrameUniforms(SunShader _shader, vector<SunNodeSentActionCondition> _conditions) {
    glUniform1i(_shader.getUniformLocation("pointLightCount"), pointLightCount);
	glUniform1i(_shader.getUniformLocation("shadowPointLightCount"), shadowPointLightCount);
    
    camera.passPerFrameUniforms(_shader);

    SunNodeSentAction action;
    action.action = "passPerFrameUniforms";
    action.parameters["shader"] = &_shader;
    action.conditions = _conditions;
    action.recursive = true;

    sendAction(action, rootRenderableNode);
}

void SunScene::passPerFrameUniformsAction(SunNodeSentAction _action) {    
    SunShader _shader = *(SunShader *)_action.parameters["shader"];
    vector<SunNodeSentActionCondition> _conditions = *(vector<SunNodeSentActionCondition> *)_action.parameters["conditions"];
    
    glUniform1i(_shader.getUniformLocation("pointLightCount"), pointLightCount);
	glUniform1i(_shader.getUniformLocation("shadowPointLightCount"), shadowPointLightCount);
    
    camera.passPerFrameUniforms(_shader);

    SunNodeSentAction action;
    action.action = "passPerFrameUniforms";
    action.parameters["shader"] = &_shader;
	action.parameters["usedTextureUnits"] = _action.parameters["usedTextureUnits"];
    action.conditions = _conditions;
    action.recursive = true;

    sendAction(action, rootRenderableNode);
}

