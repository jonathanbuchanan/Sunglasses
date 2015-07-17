//
//  Scene.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/12/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_Scene_h
#define OpenGL_Test_3_Scene_h

using namespace std;

#include "./Libraries/glm/glm.hpp"
#include "./Libraries/glm/gtc/matrix_transform.hpp"

#include "pugixml.hpp"

#include <functional>

#include "./Graphics/SunTextRenderer.h"
#include "./Graphics/GUI/SunGUISystem.h"
#include "./Graphics/SunCamera.h"
#include "./Graphics/SunRenderer.h"
#include "./Graphics/SunTextRenderer.h"
#include "./SunObject.h"
#include "./SunDirectionalLightObject.h"
#include "./SunPointLightObject.h"
#include "./SunSpotlightObject.h"
#include "./SunButtonState.h"

// Definition of SunObjectType (NEEDS A HOME)

enum SunObjectType {
    SunObjectTypePhysical,
    SunObjectTypePointLight,
    SunObjectTypeDirectionaLight
};

class SunScene : public SunObject {
public:
    // GUIsystem
    SunGUISystem *GUIsystem;
    
    // Root renderable node
    SunObject *rootRenderableNode;
    
    // Camera
    SunCamera camera;
    GLboolean doCameraInput = true;
    
    // Renderer and Text Renderer
    SunRenderer renderer;
    SunTextRenderer textRenderer;
    
    // Pointer to window
    GLFWwindow *window;
    
    SunScene() {
        // Normalize all physical properties
        position = glm::vec3(0, 0, 0);
        rotation = glm::vec3(0, 0, 0);
        scale = glm::vec3(1.0, 1.0, 1.0);
        rootNode = this;
        
        // Initialize the property map
        initializeDefaultPropertyAndFunctionMap();
    }
    
    SunScene(const char *filepath, GLFWwindow *_window) {
        // Normalize all physical properties
        position = glm::vec3(0, 0, 0);
        rotation = glm::vec3(0, 0, 0);
        scale = glm::vec3(1.0, 1.0, 1.0);
        rootNode = this;
        
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
                name = attribute.value();
            } else if (strcmp(attribute.name() ,"GUISystem") == 0) {
                GUIsystem = new SunGUISystem(attribute.value(), window, this);
            }
        }
        
        textRenderer = SunTextRenderer();
        textRenderer.initialize();
        
        rootRenderableNode = new SunObject();
        addSubNode(rootRenderableNode);
        
        // Process the XML scene node
        processXMLSceneNode(scene);
        
        GUIsystem->loadFonts(&textRenderer);
    }
    
    void initializeDefaultPropertyAndFunctionMap() {
        SunObject::initializeDefaultPropertyAndFunctionMap();
        
        type = "scene";
        
        propertyMap["doCameraInput"] = SunNodeProperty(&doCameraInput, SunNodePropertyTypeBool);
        
        functionMap["render"] = bind(&SunScene::render, this, std::placeholders::_1);
        functionMap["renderGUISystem"] = bind(&SunScene::renderGUISystem, this, std::placeholders::_1);
        functionMap["passPerFrameUniforms"] = bind(&SunScene::passPerFrameUniformsAction, this, std::placeholders::_1);
    }
    
    void processXMLSceneNode(pugi::xml_node _node) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "objects") == 0) {
                processXMLObjectsNode(node, rootRenderableNode);
            } else if (strcmp(node.name(), "camera") == 0) {
                processXMLCameraNode(node);
            } else if (strcmp(node.name(), "renderer") == 0)
                processXMLRendererNode(node);
        }
    }
    
    void processXMLCameraNode(pugi::xml_node _node) {
        // Projection type and FOV
        SunCameraProjectionType projection;
        GLfloat FOV;
        GLfloat width = 0.0f;
        GLfloat height = 0.0f;
        GLfloat yaw = 0.0f;
        GLfloat pitch = 0.0f;
        
        // Loop through the attributes
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "projection") == 0) {
                if (strcmp(attribute.value(), "perspective") == 0)
                    projection = SunCameraProjectionTypePerspective;
                else if (strcmp(attribute.value(), "orthographic") == 0)
                    projection = SunCameraProjectionTypeOrthographic;
            } else if (strcmp(attribute.name(), "FOV") == 0)
                FOV = attribute.as_float();
            else if (strcmp(attribute.name(), "yaw") == 0)
                yaw = attribute.as_float();
            else if (strcmp(attribute.name(), "pitch") == 0)
                pitch = attribute.as_float();
            else if (strcmp(attribute.name(), "width") == 0)
                width = attribute.as_float();
            else if (strcmp(attribute.name(), "height") == 0)
                height = attribute.as_float();
        }
        
        // Create the camera object
        camera = SunCamera(projection, FOV, width, height, yaw, pitch);
        
        // Loop through property nodes
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            processXMLCameraPropertyNode(node, &camera);
        }
    }
    
    void processXMLRendererNode(pugi::xml_node _node) {
        SunRenderingMode renderMode;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "mode") == 0) {
                if (strcmp(attribute.value(), "deferred-shading") == 0)
                    renderMode = SunRenderingModeDeferredShading;
                else if (strcmp(attribute.value(), "forward") == 0)
                    renderMode = SunRenderingModeForward;
            }
        }
        
        renderer = SunRenderer(renderMode);
        
        renderer.scene = this;
        renderer.window = window;
        
        renderer.initialize();
    }
    
    void processXMLCameraPropertyNode(pugi::xml_node _node, SunCamera *_camera) {
        if (strcmp(_node.name(), "position-x") == 0)
            _camera->position.x = _node.text().as_float();
        else if (strcmp(_node.name(), "position-y") == 0)
            _camera->position.y = _node.text().as_float();
        else if (strcmp(_node.name(), "position-z") == 0)
            _camera->position.z = _node.text().as_float();
    }
    
    void processXMLObjectsNode(pugi::xml_node _node, SunObject *_superObject) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            processXMLObjectNode(node, _superObject);
        }
    }
    
    void processXMLObjectNode(pugi::xml_node _node, SunObject *_superObject) {
        string name;
        string model;
        SunObjectType type;
        SunObjectMaterial material;
        SunMeshRenderType renderType;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "name") == 0)
                name = attribute.value();
            else if (strcmp(attribute.name(), "model") == 0)
                model = attribute.value();
            else if (strcmp(attribute.name(), "type") == 0) {
                if (strcmp(attribute.value(), "Physical") == 0)
                    type = SunObjectTypePhysical;
                else if (strcmp(attribute.value(), "PointLight") == 0)
                    type = SunObjectTypePointLight;
                else if (strcmp(attribute.value(), "DirectionalLight") == 0)
                    type = SunObjectTypeDirectionaLight;
            } else if (strcmp(attribute.name(), "textured") == 0) {
                if (attribute.as_bool() == true)
                    renderType = SunMeshRenderTypeTextured;
                else
                    renderType = SunMeshRenderTypeSolid;
            } else if (strcmp(attribute.name(), "animated") == 0) {
                
            }
        }
        
        if (type == SunObjectTypePhysical) {
            SunObject *object;
            object = new SunObject(name, model);
            
            object->material = material;
            object->renderType = renderType;
            
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "objects") == 0)
                    processXMLObjectsNode(node, object);
                else
                    processXMLPhysicalObjectPropertyNode(node, object);
            }
            
            _superObject->addSubNode(object);
        } else if (type == SunObjectTypePointLight) {
            SunPointLightObject *object = new SunPointLightObject(name);
            
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "objects") == 0)
                    processXMLObjectNode(node, object);
                else
                    processXMLPointLightObjectPropertyNode(node, object);
            }
            
            _superObject->addSubNode(object);
        } else if (type == SunObjectTypeDirectionaLight) {
            SunDirectionalLightObject *object = new SunDirectionalLightObject(name);
            
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "objects") == 0)
                    processXMLObjectNode(node, object);
                else
                    processXMLDirectionalLightObjectPropertyNode(node, object);
            }
            
            _superObject->addSubNode(object);
        }
    }
    
    void processXMLPhysicalObjectPropertyNode(pugi::xml_node _node, SunObject *_object) {
        if (strcmp(_node.name(), "position-x") == 0)
            _object->position.x = _node.text().as_float();
        else if (strcmp(_node.name(), "position-y") == 0)
            _object->position.y = _node.text().as_float();
        else if (strcmp(_node.name(), "position-z") == 0)
            _object->position.z = _node.text().as_float();
        else if (strcmp(_node.name(), "rotation-x") == 0)
            _object->rotation.x = _node.text().as_float();
        else if (strcmp(_node.name(), "rotation-y") == 0)
            _object->rotation.y = _node.text().as_float();
        else if (strcmp(_node.name(), "rotation-z") == 0)
            _object->rotation.z = _node.text().as_float();
        else if (strcmp(_node.name(), "scale-x") == 0)
            _object->scale.x = _node.text().as_float();
        else if (strcmp(_node.name(), "scale-y") == 0)
            _object->scale.y = _node.text().as_float();
        else if (strcmp(_node.name(), "scale-z") == 0)
            _object->scale.z = _node.text().as_float();
        else if (strcmp(_node.name(), "material-r") == 0)
            _object->material.color.r = _node.text().as_float();
        else if (strcmp(_node.name(), "material-g") == 0)
            _object->material.color.g = _node.text().as_float();
        else if (strcmp(_node.name(), "material-b") == 0)
            _object->material.color.b = _node.text().as_float();
        else if (strcmp(_node.name(), "material-shininess") == 0)
            _object->material.shininess = _node.text().as_float();
    }
    
    void processXMLPointLightObjectPropertyNode(pugi::xml_node _node, SunPointLightObject *_object) {
        if (strcmp(_node.name(), "position-x") == 0)
            _object->position.x = _node.text().as_float();
        else if (strcmp(_node.name(), "position-y") == 0)
            _object->position.y = _node.text().as_float();
        else if (strcmp(_node.name(), "position-z") == 0)
            _object->position.z = _node.text().as_float();
        else if (strcmp(_node.name(), "rotation-x") == 0)
            _object->rotation.x = _node.text().as_float();
        else if (strcmp(_node.name(), "rotation-y") == 0)
            _object->rotation.y = _node.text().as_float();
        else if (strcmp(_node.name(), "rotation-z") == 0)
            _object->rotation.z = _node.text().as_float();
        else if (strcmp(_node.name(), "scale-x") == 0)
            _object->scale.x = _node.text().as_float();
        else if (strcmp(_node.name(), "scale-y") == 0)
            _object->scale.y = _node.text().as_float();
        else if (strcmp(_node.name(), "scale-z") == 0)
            _object->scale.z = _node.text().as_float();
        else if (strcmp(_node.name(), "color-r") == 0)
            _object->color.r = _node.text().as_float();
        else if (strcmp(_node.name(), "color-g") == 0)
            _object->color.g = _node.text().as_float();
        else if (strcmp(_node.name(), "color-b") == 0)
            _object->color.b = _node.text().as_float();
    }
    
    void processXMLDirectionalLightObjectPropertyNode(pugi::xml_node _node, SunDirectionalLightObject *_object) {
        if (strcmp(_node.name(), "position-x") == 0)
            _object->position.x = _node.text().as_float();
        else if (strcmp(_node.name(), "position-y") == 0)
            _object->position.y = _node.text().as_float();
        else if (strcmp(_node.name(), "position-z") == 0)
            _object->position.z = _node.text().as_float();
        else if (strcmp(_node.name(), "rotation-x") == 0)
            _object->rotation.x = _node.text().as_float();
        else if (strcmp(_node.name(), "rotation-y") == 0)
            _object->rotation.y = _node.text().as_float();
        else if (strcmp(_node.name(), "rotation-z") == 0)
            _object->rotation.z = _node.text().as_float();
        else if (strcmp(_node.name(), "scale-x") == 0)
            _object->scale.x = _node.text().as_float();
        else if (strcmp(_node.name(), "scale-y") == 0)
            _object->scale.y = _node.text().as_float();
        else if (strcmp(_node.name(), "scale-z") == 0)
            _object->scale.z = _node.text().as_float();
        else if (strcmp(_node.name(), "color-r") == 0)
            _object->color.r = _node.text().as_float();
        else if (strcmp(_node.name(), "color-g") == 0)
            _object->color.g = _node.text().as_float();
        else if (strcmp(_node.name(), "color-b") == 0)
            _object->color.b = _node.text().as_float();
    }
    
    void cycle(map<int, SunButtonState> _buttons, GLfloat _deltaTime) {
        update(_buttons);
        renderer.render(_deltaTime);
    }
    
    void update(map<int, SunButtonState> _buttons) {
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
    }
    
    virtual void render(SunNodeSentAction _action) {
        map<string, SunShader> _shaders = *(map<string, SunShader> *)_action.parameters["shaderMap"];
        GLfloat _deltaTime = *(GLfloat *)_action.parameters["deltaTime"];
        
        // Force sub-objects to render

        SunNodeSentAction solidAction;
        solidAction.action = "render";
        solidAction.parameters["shader"] = &_shaders["solid"];
        solidAction.parameters["renderType"] = new int(SunMeshRenderTypeSolid);
        solidAction.parameters["deltaTime"] = &_deltaTime;
        solidAction.recursive = true;

        SunNodeSentAction texturedAction;
        texturedAction.action = "render";
        texturedAction.parameters["shader"] = &_shaders["textured"];
        texturedAction.parameters["rendertype"] = new int(SunMeshRenderTypeTextured);
        texturedAction.parameters["deltaTime"] = &_deltaTime;
        texturedAction.recursive = true;

        _shaders["solid"].use();
        passPerFrameUniforms(_shaders["solid"]);
        sendAction(solidAction, rootRenderableNode);

        _shaders["textured"].use();
        passPerFrameUniforms(_shaders["textured"]);
        sendAction(texturedAction, rootRenderableNode);
    }
    
    void renderGUISystem(SunNodeSentAction _action) {
        SunNodeSentAction GUIAction;
        GUIAction.action = "render";
        GUIAction.parameters["textRenderer"] = &textRenderer;
        
        sendAction(GUIAction, GUIsystem);
    }
    
    void passPerFrameUniforms(SunShader _shader) {
        camera.passPerFrameUniforms(_shader);
        
        SunNodeSentAction action;
        action.action = "passPerFrameUniforms";
        action.parameters["shader"] = &_shader;
        action.recursive = true;
        
        sendAction(action, rootRenderableNode);
    }
    
    void passPerFrameUniforms(SunShader _shader, vector<SunNodeSentActionCondition> _conditions) {
        camera.passPerFrameUniforms(_shader);
        
        SunNodeSentAction action;
        action.action = "passPerFrameUniforms";
        action.parameters["shader"] = &_shader;
        action.conditions = _conditions;
        action.recursive = true;
        
        sendAction(action, rootRenderableNode);
    }
    
    void passPerFrameUniformsAction(SunNodeSentAction _action) {
        SunShader _shader = *(SunShader *)_action.parameters["shader"];
        vector<SunNodeSentActionCondition> _conditions = *(vector<SunNodeSentActionCondition> *)_action.parameters["conditions"];
        
        camera.passPerFrameUniforms(_shader);
        
        SunNodeSentAction action;
        action.action = "passPerFrameUniforms";
        action.parameters["shader"] = &_shader;
        action.conditions = _conditions;
        action.recursive = true;
        
        sendAction(action, rootRenderableNode);
    }
    
private:
    
};

#endif
