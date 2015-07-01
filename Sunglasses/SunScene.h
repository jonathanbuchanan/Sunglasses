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

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "pugixml.hpp"

#include "SunCamera.h"
#include "SunObject.h"
#include "SunDirectionalLightObject.h"
#include "SunPointLightObject.h"
#include "SunSpotlightObject.h"
#include "SunCubemapObject.h"
#include "SunButtonState.h"

// Definition of SunObjectType (NEEDS A HOME)

enum SunObjectType {
    SunObjectTypePhysical,
    SunObjectTypePointLight,
    SunObjectTypeDirectionaLight
};

class SunScene : public SunObject {
public:
    // GUIsystem
    SunGUISystem GUIsystem;
    
    // Camera
    SunCamera camera;
    
    // Pointer to window
    GLFWwindow *window;
    
    SunScene() {
        // Normalize all physical properties
        position = glm::vec3(0, 0, 0);
        rotation = glm::vec3(0, 0, 0);
        scale = glm::vec3(1.0, 1.0, 1.0);
        
        // Initialize the property map
        initializeDefaultPropertyMap();
    }
    
    SunScene(const char *filepath, GLFWwindow *_window) {
        // Normalize all physical properties
        position = glm::vec3(0, 0, 0);
        rotation = glm::vec3(0, 0, 0);
        scale = glm::vec3(1.0, 1.0, 1.0);
        
        // Set the window
        window = _window;
        
        // Initialize the property map
        initializeDefaultPropertyMap();
        
        // Set up the XML Parsing
        pugi::xml_document document;
        document.load_file(filepath);
        
        pugi::xml_node scene = document.child("scene");
        
        for (pugi::xml_attribute attribute = scene.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "name") == 0) {
                name = attribute.value();
            } else if (strcmp(attribute.name() ,"GUISystem") == 0) {
                GUIsystem = SunGUISystem(attribute.value(), window);
            }
        }
        
        // Process the XML scene node
        processXMLSceneNode(scene);
    }
    
    void processXMLSceneNode(pugi::xml_node _node) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "objects") == 0) {
                processXMLObjectsNode(node, this);
            } else if (strcmp(node.name(), "camera") == 0) {
                processXMLCameraNode(node);
            }
        }
    }
    
    void processXMLCameraNode(pugi::xml_node _node) {
        // Projection type and FOV
        SunCameraProjectionType projection;
        GLfloat FOV;
        
        // Loop through the attributes
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "projection") == 0) {
                if (strcmp(attribute.value(), "perspective") == 0)
                    projection = SunCameraProjectionTypePerspective;
                else if (strcmp(attribute.value(), "orthographic") == 0)
                    projection = SunCameraProjectionTypeOrthographic;
            } else if (strcmp(attribute.name(), "FOV") == 0)
                FOV = attribute.as_float();
        }
        
        // Create the camera object
        camera = SunCamera(projection, FOV);
        
        // Loop through property nodes
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            processXMLCameraPropertyNode(node, &camera);
        }
    }
    
    void processXMLCameraPropertyNode(pugi::xml_node _node, SunCamera *_camera) {
        if (strcmp(_node.name(), "position-x") == 0)
            _camera->position.x = _node.text().as_float();
        else if (strcmp(_node.name(), "position-y") == 0)
            _camera->position.y = _node.text().as_float();
        else if (strcmp(_node.name(), "position-z") == 0)
            _camera->position.z = _node.text().as_float();
        else if (strcmp(_node.name(), "direction-x") == 0)
            _camera->direction.x = _node.text().as_float();
        else if (strcmp(_node.name(), "direction-y") == 0)
            _camera->direction.y = _node.text().as_float();
        else if (strcmp(_node.name(), "direction-z") == 0)
            _camera->direction.z = _node.text().as_float();
    }
    
    void processXMLObjectsNode(pugi::xml_node _node, SunObject *_superObject) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            processXMLObjectNode(node, _superObject);
        }
    }
    
    void processXMLObjectNode(pugi::xml_node _node, SunObject *_superObject) {
        int tag;
        string name;
        string model;
        SunObjectType type;
        SunObjectMaterial material;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "tag") == 0)
                tag = attribute.as_int();
            else if (strcmp(attribute.name(), "name") == 0)
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
                    material.textured = true;
                else
                    material.textured = false;
            } else if (strcmp(attribute.name(), "animated") == 0) {
                if (attribute.as_bool() == true)
                    material.animated = true;
                else
                    material.animated = false;
            }
        }
        
        if (type == SunObjectTypePhysical) {
            SunObject *object = new SunObject(tag, name, model);
            object->material = material;
            
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "objects") == 0)
                    processXMLObjectsNode(node, object);
                else
                    processXMLPhysicalObjectPropertyNode(node, object);
            }
            
            _superObject->addSubObject(object);
        } else if (type == SunObjectTypePointLight) {
            SunPointLightObject *object = new SunPointLightObject(tag, name);
            
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "objects") == 0)
                    processXMLObjectNode(node, object);
                else
                    processXMLPointLightObjectPropertyNode(node, object);
            }
            
            _superObject->addSubObject(object);
        } else if (type == SunObjectTypeDirectionaLight) {
            SunDirectionalLightObject *object = new SunDirectionalLightObject(tag, name);
            
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "objects") == 0)
                    processXMLObjectNode(node, object);
                else
                    processXMLDirectionalLightObjectPropertyNode(node, object);
            }
            
            _superObject->addSubObject(object);
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
    
    void update(map<int, SunButtonState> _buttons) {
        // Get the position of the mouse
        GLdouble xPosition, yPosition;
        glfwGetCursorPos(window, &xPosition, &yPosition);
        
        // Map Cursor Position to NDC
        
        GLdouble normalizedXPosition, normalizedYPosition;
        
        normalizedXPosition = (xPosition - 400) / 400;
        normalizedYPosition = -(yPosition - 300) / 300;
        
        // Force the GUI system to update
        GUIsystem.update(_buttons, normalizedXPosition, normalizedYPosition);
        
        // Force sub-objects to update
        SunObject::update();
    }
    
    void render(SunShader _shader, GLfloat _deltaTime) {
        // Force sub-objects to render
        SunObject::render(_shader, _deltaTime);
    }
    
private:
    
};

#endif
