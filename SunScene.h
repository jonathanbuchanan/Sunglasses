//
//  Scene.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/12/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_Scene_h
#define OpenGL_Test_3_Scene_h

#include "./Physics/SunPhysicsSimulator.h"
#include "./Graphics/SunTextRenderer.h"
#include "./Graphics/GUI/SunGUISystem.h"
#include "./Graphics/SunCamera.h"
#include "./Graphics/SunRenderer.h"
#include "./Graphics/SunRenderingNode.h"
#include "./Graphics/SunTextRenderer.h"
#include "./Audio/SunSoundListener.h"
#include "./Audio/SunSoundBufferStorage.h"
#include "./Audio/SunMusicObject.h"
#include "./SunObject.h"
#include "./SunDirectionalLightObject.h"
#include "./SunPointLightObject.h"
#include "./SunButtonState.h"

// Definition of SunObjectType (NEEDS A HOME)

enum SunObjectType {
    SunObjectTypePhysical,
    SunObjectTypePointLight,
    SunObjectTypeDirectionaLight
};

class SunScene : public SunObject {
public:
    SunScene();
    SunScene(const char *filepath, GLFWwindow *_window);
    
    void initializeDefaultPropertyAndFunctionMap();
    
    void processXMLSceneNode(pugi::xml_node _node) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "scenedata") == 0) {
                processXMLSceneDataNode(node);
            } else if (strcmp(node.name(), "physicsworld") == 0) {
                processXMLPhysicsWorldNode(node);
            } else if (strcmp(node.name(), "objects") == 0) {
                processXMLObjectsNode(node, rootRenderableNode);
            } else if (strcmp(node.name(), "camera") == 0) {
                processXMLCameraNode(node);
            } else if (strcmp(node.name(), "listener") == 0) {
                processXMLListenerNode(node);
            } else if (strcmp(node.name(), "renderer") == 0)
                processXMLRendererNode(node);
        }
    }
    
    void processXMLSceneDataNode(pugi::xml_node _node) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "pointlights") == 0)
                pointLightCount = node.text().as_int();
        }
    }
    
    void processXMLPhysicsWorldNode(pugi::xml_node _node) {
        SunPhysicsWorld world;
        
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "gravity") == 0)
                world.setGravity(processXMLPhysicsWorldGravityNode(node));
        }
        physicsSimulator.setWorld(world);
    }
    
    SunPhysicsForce processXMLPhysicsWorldGravityNode(pugi::xml_node _node) {
        float x;
        float y;
        float z;
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "x") == 0)
                x = node.text().as_float();
            else if (strcmp(node.name(), "y") == 0)
                y = node.text().as_float();
            else if (strcmp(node.name(), "z") == 0)
                z = node.text().as_float();
        }
        SunPhysicsForce gravity = SunPhysicsForce(glm::vec3(x, y, z));
        gravity.setScalesWithMass(true);
        return gravity;
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
    
    void processXMLCameraPropertyNode(pugi::xml_node _node, SunCamera *_camera) {
        if (strcmp(_node.name(), "position-x") == 0)
            _camera->setPositionX(_node.text().as_float());
        else if (strcmp(_node.name(), "position-y") == 0)
            _camera->setPositionY(_node.text().as_float());
        else if (strcmp(_node.name(), "position-z") == 0)
            _camera->setPositionZ(_node.text().as_float());
    }
    
    void processXMLListenerNode(pugi::xml_node _node) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling())
            if (strcmp(node.name(), "music") == 0)
                processXMLMusicNode(node);
    }
    
    void processXMLMusicNode(pugi::xml_node _node) {
        string file;
        string name;
        bool loops;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "file") == 0)
                file = attribute.value();
            else if (strcmp(attribute.name(), "name") == 0)
                name = attribute.value();
            else if (strcmp(attribute.name(), "loops") == 0)
                loops = attribute.as_bool();
            else if (strcmp(attribute.name(), "autoplay") == 0)
                autoplay = attribute.as_bool();
        }
        
        music = new SunMusicObject(file, name, loops);
    }
    
    void processXMLRendererNode(pugi::xml_node _node) {
        renderer = SunRenderer();
        
        renderer.setSceneNode(this);
        renderer.setWindow(window);
        
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "pipeline") == 0)
                processXMLRendererPipelineNode(node, &renderer);
        }
    }
    
    void processXMLRendererPipelineNode(pugi::xml_node _node, SunRenderer *_renderer) {
        vector<SunRenderingNode *> renderNodes;
        
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "rendernode") == 0) {
                renderNodes.push_back(processXMLRenderNode(node, _renderer));
            }
        }
        
        SunRenderingNode *root;
        
        for (int i = 0; i < renderNodes.size(); i++) {
            switch(renderNodes[i]->getRenderingType()) {
                case SunRenderingNodeTypeRoot:
                    renderNodes[i]->setRootNode(renderNodes[i]);
                    root = renderNodes[i];
                    break;
                case SunRenderingNodeTypeIntermediate:
                    for (int j = 0; j < renderNodes[i]->getInputs().size(); j++) {
                        SunNode *parent;
                        root->findPointerNodeWithName(renderNodes[i]->getInputAtIndex(j).linkName, parent);
                        renderNodes[i]->getInputAtIndex(j).link = (SunRenderingNode *)parent;
                        parent->addSubNode(renderNodes[i]);
                    }
                    if (renderNodes[i]->getInputs().size() == 0)
                        root->addSubNode(renderNodes[i]);
                    break;
                case SunRenderingNodeTypeEnd:
                    for (int j = 0; j < renderNodes[i]->getInputs().size(); j++) {
                        SunNode *parent;
                        root->findPointerNodeWithName(renderNodes[i]->getInputAtIndex(j).linkName, parent);
                        renderNodes[i]->getInputAtIndex(j).link = (SunRenderingNode *)parent;
                        parent->addSubNode(renderNodes[i]);
                    }
                    break;
                case SunRenderingNodeTypeOnly:
                    renderNodes[i]->setRootNode(renderNodes[i]);
                    root = renderNodes[i];
                    break;
            }
        }
        
        renderer.setRootRenderNode(root);
   }
    
    void processXMLRenderNode(pugi::xml_node _node, SunRenderer *_renderer, SunRenderingNode &_renderingNode) {
        string name;
        SunRenderingNodeType type;
        SunRenderingNodeShaderType shaderType;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "name") == 0)
                name = attribute.value();
            else if (strcmp(attribute.name(), "type") == 0) {
                if (strcmp(attribute.value(), "root") == 0)
                    type = SunRenderingNodeTypeRoot;
                else if (strcmp(attribute.value(), "intermediate") == 0)
                    type = SunRenderingNodeTypeIntermediate;
                else if (strcmp(attribute.value(), "end") == 0)
                    type = SunRenderingNodeTypeEnd;
            } else if (strcmp(attribute.name(), "shadertype") == 0) {
                if (strcmp(attribute.value(), "Scene") == 0) {
                    shaderType = SunRenderingNodeShaderTypeScene;
                } else if (strcmp(attribute.value(), "Quad") == 0) {
                    shaderType = SunRenderingNodeShaderTypeQuad;
                }
            }
        }
        
        _renderingNode = SunRenderingNode(name);
        _renderingNode.setRenderingType(type);
        _renderingNode.setShaderType(shaderType);
        _renderingNode.setRootNode(&_renderingNode);
        _renderingNode.setSceneNode(this);
        
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "inputs") == 0)
                processXMLRenderNodeInputs(node, &_renderingNode);
            else if (strcmp(node.name(), "outputs") == 0)
                processXMLRenderNodeOutputs(node, &_renderingNode);
            else if (strcmp(node.name(), "shaders") == 0)
                processXMLRenderNodeShaders(node, &_renderingNode);
        }
        
        _renderingNode.initialize();
    }
   
    SunRenderingNode * processXMLRenderNode(pugi::xml_node _node, SunRenderer *_renderer) {
        string name;
        SunRenderingNodeType type;
        SunRenderingNodeShaderType shaderType;
        string POVtype;
        string POV;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "name") == 0)
                name = attribute.value();
            else if (strcmp(attribute.name(), "type") == 0) {
                if (strcmp(attribute.value(), "root") == 0)
                    type = SunRenderingNodeTypeRoot;
                else if (strcmp(attribute.value(), "intermediate") == 0)
                    type = SunRenderingNodeTypeIntermediate;
                else if (strcmp(attribute.value(), "end") == 0)
                    type = SunRenderingNodeTypeEnd;
                else if (strcmp(attribute.value(), "only") == 0)
                    type = SunRenderingNodeTypeOnly;
            } else if (strcmp(attribute.name(), "shadertype") == 0) {
                if (strcmp(attribute.value(), "Scene") == 0) {
                    shaderType = SunRenderingNodeShaderTypeScene;
                } else if (strcmp(attribute.value(), "Quad") == 0) {
                    shaderType = SunRenderingNodeShaderTypeQuad;
                }
            } else if (strcmp(attribute.name(), "POVtype") == 0)
                POVtype = attribute.value();
            else if (strcmp(attribute.name(), "POV") == 0)
                POV = attribute.value();
        }
        
        SunRenderingNode *_renderingNode = new SunRenderingNode(name);
        _renderingNode->setRenderingType(type);
        _renderingNode->setShaderType(shaderType);
        _renderingNode->setSceneNode(this);
        _renderingNode->setPOVType(POVtype);
        _renderingNode->setPOV(POV);
        
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "inputs") == 0)
                processXMLRenderNodeInputs(node, _renderingNode);
            else if (strcmp(node.name(), "outputs") == 0)
                processXMLRenderNodeOutputs(node, _renderingNode);
            else if (strcmp(node.name(), "shaders") == 0)
                processXMLRenderNodeShaders(node, _renderingNode);
            else if (strcmp(node.name(), "textures") == 0)
                processXMLRenderNodeTextures(node, _renderingNode);
            else if (strcmp(node.name(), "uniforms") == 0)
                processXMLRenderNodeUniforms(node, _renderingNode);
        }
        
        _renderingNode->initialize();
        return _renderingNode;
    }
    
    void processXMLRenderNodeInputs(pugi::xml_node _node, SunRenderingNode *_renderNode) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling())
            processXMLRenderNodeInput(node, _renderNode);
    }
    
    void processXMLRenderNodeInput(pugi::xml_node _node, SunRenderingNode *_renderNode) {
        SunRenderingNodeInput input;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "node") == 0)
                input.linkName = attribute.value();
            else if (strcmp(attribute.name(), "data") == 0) {
                if (strcmp(attribute.value(), "position") == 0)
                    input.type = SunRenderingNodeDataTypePosition;
                else if (strcmp(attribute.value(), "normal") == 0)
                    input.type = SunRenderingNodeDataTypeNormal;
                else if (strcmp(attribute.value(), "color") == 0)
                    input.type = SunRenderingNodeDataTypeColor;
                else if (strcmp(attribute.value(), "depth") == 0)
                    input.type = SunRenderingNodeDataTypeDepth;
            } else if (strcmp(attribute.name(), "name") == 0)
                input.name = attribute.value();
            else if (strcmp(attribute.name(), "format") == 0) {
                if (strcmp(attribute.value(), "RGB16F") == 0)
                    input.format = SunRenderingNodeDataFormatRGB16F;
                else if (strcmp(attribute.value(), "RGBA16F") == 0)
                    input.format = SunRenderingNodeDataFormatRGBA16F;
                else if (strcmp(attribute.value(), "16F") == 0)
                    input.format = SunRenderingNodeDataFormat16F;
            } else if (strcmp(attribute.name(), "slot") == 0)
                input.slot = attribute.as_int();
            else if (strcmp(attribute.name(), "texturetype") == 0) {
                if (strcmp(attribute.value(), "2D") == 0)
                    input.textureType = SunRenderingNodeTextureType2D;
                else if (strcmp(attribute.value(), "Cubemap") == 0)
                    input.textureType = SunRenderingNodeTextureTypeCubemap;
            }
        }
        
        _renderNode->addInputToInputs(input);
    }
    
    void processXMLRenderNodeOutputs(pugi::xml_node _node, SunRenderingNode *_renderNode) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling())
            processXMLRenderNodeOutput(node, _renderNode);
    }
    
    void processXMLRenderNodeOutput(pugi::xml_node _node, SunRenderingNode *_renderNode) {
        SunRenderingNodeOutput output;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "data") == 0) {
                if (strcmp(attribute.value(), "position") == 0)
                    output.type = SunRenderingNodeDataTypePosition;
                else if (strcmp(attribute.value(), "normal") == 0)
                    output.type = SunRenderingNodeDataTypeNormal;
                else if (strcmp(attribute.value(), "color") == 0)
                    output.type = SunRenderingNodeDataTypeColor;
                else if (strcmp(attribute.value(), "occlusion") == 0)
                    output.type = SunRenderingNodeDataTypeOcclusion;
                else if (strcmp(attribute.value(), "depth") == 0)
                    output.type = SunRenderingNodeDataTypeDepth;
            } else if (strcmp(attribute.name(), "format") == 0) {
                if (strcmp(attribute.value(), "RGB16F") == 0)
                    output.format = SunRenderingNodeDataFormatRGB16F;
                else if (strcmp(attribute.value(), "RGBA16F") == 0)
                    output.format = SunRenderingNodeDataFormatRGBA16F;
                else if (strcmp(attribute.value(), "16F") == 0)
                    output.format = SunRenderingNodeDataFormat16F;
            } else if (strcmp(attribute.name(), "slot") == 0)
                output.slot = attribute.as_int();
            else if (strcmp(attribute.name(), "width") == 0)
                output.size.x = attribute.as_float();
            else if (strcmp(attribute.name(), "height") == 0)
                output.size.y = attribute.as_float();
            else if (strcmp(attribute.name(), "texturetype") == 0) {
                if (strcmp(attribute.value(), "2D") == 0)
                    output.textureType = SunRenderingNodeTextureType2D;
                else if (strcmp(attribute.value(), "Cubemap") == 0)
                    output.textureType = SunRenderingNodeTextureTypeCubemap;
            }
        }
        
        _renderNode->addOutputToOutputs(output);
    }
    
    void processXMLRenderNodeShaders(pugi::xml_node _node, SunRenderingNode *_renderNode) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling())
            processXMLRenderNodeShader(node, _renderNode);
    }
    
    void processXMLRenderNodeShader(pugi::xml_node _node, SunRenderingNode *_renderNode) {
        vector<string> shaderSources;
        vector<string> tempTypes;
        vector<SunShaderSourceType> types;
        string preprocessor;
        SunRenderingNodeShaderType type;
        string _type;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "type") == 0) {
                _type = attribute.value();
                if (strcmp(attribute.value(), "scene_textured") == 0)
                    type = SunRenderingNodeShaderTypeSceneTextured;
                else if (strcmp(attribute.value(), "scene_solid") == 0)
                    type = SunRenderingNodeShaderTypeSceneSolid;
                else if (strcmp(attribute.value(), "quad") == 0)
                    type = SunRenderingNodeShaderTypeQuad;
            } else if (strcmp(attribute.name(), "shaders") == 0)
                shaderSources = splitString(attribute.value(), *",");
            else if (strcmp(attribute.name(), "shadertypes") == 0)
                tempTypes = splitString(attribute.value(), *",");
            else if (strcmp(attribute.name(), "preprocessor") == 0)
                preprocessor = attribute.value();
        }
        
        for (int i = 0; i < tempTypes.size(); i++) {
            if (tempTypes[i] == "vertex")
                types.push_back(SunShaderSourceTypeVertex);
            else if (tempTypes[i] == "geometry")
                types.push_back(SunShaderSourceTypeGeometry);
            else if (tempTypes[i] == "fragment")
                types.push_back(SunShaderSourceTypeFragment);
        }
        
        SunRenderingNodeShader shader = SunRenderingNodeShader(shaderSources, types, preprocessor, type);
        
        _renderNode->addShaderForString(_type, shader);
    }
    
    void processXMLRenderNodeTextures(pugi::xml_node _node, SunRenderingNode *_renderNode) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling())
            processXMLRenderNodeTexture(node, _renderNode);
    }
    
    void processXMLRenderNodeTexture(pugi::xml_node _node, SunRenderingNode *_renderNode) {
        string name;
        SunTextureType type;
        GLuint width;
        GLuint height;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "name") == 0)
                name = attribute.value();
            else if (strcmp(attribute.name(), "type") == 0) {
                if (strcmp(attribute.value(), "noise_hemisphere") == 0)
                    type = SunTextureTypeNoiseHemisphere;
            } else if (strcmp(attribute.name(), "width") == 0)
                width = attribute.as_int();
            else if (strcmp(attribute.name(), "height") == 0)
                height = attribute.as_int();
        }
        
        SunTexture texture = SunTexture(width, height, type);
        
        _renderNode->addTextureToTextures(texture);
    }
    
    void processXMLRenderNodeUniforms(pugi::xml_node _node, SunRenderingNode *_renderNode) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling())
            if (strcmp(node.name(), "hemispheresamplekernel") == 0)
                processXMLRenderNodeHemisphereSampleKernel(node, _renderNode);
    }
    
    void processXMLRenderNodeHemisphereSampleKernel(pugi::xml_node _node, SunRenderingNode *_renderNode) {
        string name;
        GLuint sampleCount = 0;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "name") == 0)
                name = attribute.value();
            if (strcmp(attribute.name(), "samplecount") == 0)
                sampleCount = attribute.as_int();
        }
        
        SunShaderHemisphereKernelObject *kernel = new SunShaderHemisphereKernelObject(sampleCount);
        kernel->setUniformName(name);
        
        _renderNode->addUniformToUniforms(kernel);
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
        bool flipNormals;
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
            } else if (strcmp(attribute.name(), "flipnormals") == 0)
                flipNormals = attribute.as_bool();
            else if (strcmp(attribute.name(), "animated") == 0) {
                
            }
        }
        
        if (type == SunObjectTypePhysical) {
            SunObject *object;
            object = new SunObject(name, model, flipNormals);
            
            object->setName(name);
            object->setMaterial(material);
            object->setRenderType(renderType);
            
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "objects") == 0)
                    processXMLObjectsNode(node, object);
                else if (strcmp(node.name(), "colliders") == 0)
                    processXMLObjectCollidersNode(node, object);
                else if (strcmp(node.name(), "sounds") == 0)
                    processXMLObjectSoundsNode(node, object);
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
    
    void processXMLObjectCollidersNode(pugi::xml_node _node, SunObject *_object) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            processXMLObjectColliderNode(node, _object);
        }
    }
    
    void processXMLObjectColliderNode(pugi::xml_node _node, SunObject *_object) {
        string type;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "type") == 0)
                type = attribute.value();
        }
        
        if (type == "AABB") {
            SunPhysicsColliderAABB *collider = new SunPhysicsColliderAABB();
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "first-x") == 0)
                    collider->setFirstPointX(node.text().as_float());
                else if (strcmp(node.name(), "first-y") == 0)
                    collider->setFirstPointY(node.text().as_float());
                else if (strcmp(node.name(), "first-z") == 0)
                    collider->setFirstPointZ(node.text().as_float());
                else if (strcmp(node.name(), "second-x") == 0)
                    collider->setSecondPointX(node.text().as_float());
                else if (strcmp(node.name(), "second-y") == 0)
                    collider->setSecondPointY(node.text().as_float());
                else if (strcmp(node.name(), "second-z") == 0)
                    collider->setSecondPointZ(node.text().as_float());
                else if (strcmp(node.name(), "center-x") == 0)
                    collider->setPositionX(node.text().as_float());
                else if (strcmp(node.name(), "center-y") == 0)
                    collider->setPositionY(node.text().as_float());
                else if (strcmp(node.name(), "center-z") == 0)
                    collider->setPositionZ(node.text().as_float());
            }
            _object->getPhysicsObject().addCollider(collider);
        } else if (type == "Sphere") {
            SunPhysicsColliderSphere *collider = new SunPhysicsColliderSphere();
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "center-x") == 0)
                    collider->setPositionX(node.text().as_float());
                else if (strcmp(node.name(), "center-y") == 0)
                    collider->setPositionY(node.text().as_float());
                else if (strcmp(node.name(), "center-z") == 0)
                    collider->setPositionZ(node.text().as_float());
                else if (strcmp(node.name(), "radius") == 0)
                    collider->setRadius(node.text().as_float());
            }
            _object->getPhysicsObject().addCollider(collider);
        } else if (type == "Plane") {
            SunPhysicsColliderPlane *collider = new SunPhysicsColliderPlane();
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "normal-x") == 0)
                    collider->setNormalX(node.text().as_float());
                else if (strcmp(node.name(), "normal-y") == 0)
                    collider->setNormalY(node.text().as_float());
                else if (strcmp(node.name(), "normal-z") == 0)
                    collider->setNormalZ(node.text().as_float());
                else if (strcmp(node.name(), "distance") == 0)
                    collider->setDistance(node.text().as_float());
                else if (strcmp(node.name(), "reflective") == 0)
                    collider->setReflective(node.text().as_bool());
            }
            _object->getPhysicsObject().addCollider(collider);
        } else if (type == "Mesh") {
            SunPhysicsColliderMesh *collider = new SunPhysicsColliderMesh();
            for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
                if (strcmp(node.name(), "file") == 0)
                    collider->importMeshDataFromFile(node.text().as_string());
                if (strcmp(node.name(), "position-x") == 0)
                    collider->setPositionX(node.text().as_float());
                if (strcmp(node.name(), "position-y") == 0)
                    collider->setPositionY(node.text().as_float());
                if (strcmp(node.name(), "position-y") == 0)
                    collider->setPositionZ(node.text().as_float());
            }
            _object->getPhysicsObject().addCollider(collider);
        }
    }
    
    void processXMLObjectSoundsNode(pugi::xml_node _node, SunObject *_object) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling())
            processXMLObjectSoundNode(node, _object);
    }
    
    void processXMLObjectSoundNode(pugi::xml_node _node, SunObject *_object) {
        string file;
        string name;
        float minimumDistance;
        float attenuation;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "file") == 0)
                file = attribute.value();
            else if (strcmp(attribute.name(), "name") == 0)
                name = attribute.value();
            else if (strcmp(attribute.name(), "minimumDistance") == 0)
                minimumDistance = attribute.as_float();
            else if (strcmp(attribute.name(), "attenuation") == 0)
                attenuation = attribute.as_float();
        }
        
        if (storage.getBufferMap().find(name) == storage.getBufferMap().end()) {
            storage.loadSoundFromFileWithName(file, name);
        }
        
        _object->getSoundObject().addSoundFromBuffer(&storage, name, minimumDistance, attenuation);
    }
    
    void processXMLPhysicalObjectPropertyNode(pugi::xml_node _node, SunObject *_object) {
        if (strcmp(_node.name(), "position-x") == 0)
            _object->setPositionX(_node.text().as_float());
        else if (strcmp(_node.name(), "position-y") == 0)
            _object->setPositionY(_node.text().as_float());
        else if (strcmp(_node.name(), "position-z") == 0)
            _object->setPositionZ(_node.text().as_float());
        else if (strcmp(_node.name(), "rotation-x") == 0)
            _object->setRotationX(_node.text().as_float());
        else if (strcmp(_node.name(), "rotation-y") == 0)
            _object->setRotationY(_node.text().as_float());
        else if (strcmp(_node.name(), "rotation-z") == 0)
            _object->setRotationZ(_node.text().as_float());
        else if (strcmp(_node.name(), "scale-x") == 0)
            _object->setScaleX(_node.text().as_float());
        else if (strcmp(_node.name(), "scale-y") == 0)
            _object->setScaleY(_node.text().as_float());
        else if (strcmp(_node.name(), "scale-z") == 0)
            _object->setScaleZ(_node.text().as_float());
        else if (strcmp(_node.name(), "material-r") == 0)
            _object->getMaterial().color.r = _node.text().as_float();
        else if (strcmp(_node.name(), "material-g") == 0)
            _object->getMaterial().color.g = _node.text().as_float();
        else if (strcmp(_node.name(), "material-b") == 0)
            _object->getMaterial().color.b = _node.text().as_float();
        else if (strcmp(_node.name(), "material-shininess") == 0)
            _object->getMaterial().shininess = _node.text().as_float();
        else if (strcmp(_node.name(), "physicsenabled") == 0) {
            _object->setPhysicsEnabled(_node.text().as_bool());
            physicsSimulator.getWorld().addObjectToObjects(&_object->getPhysicsObject());
        } else if (strcmp(_node.name(), "mass") == 0) {
            _object->getPhysicsObject().setMass(_node.text().as_float());
        } else if (strcmp(_node.name(), "stationary") == 0) 
            _object->getPhysicsObject().setStationary(_node.text().as_bool());
        else if (strcmp(_node.name(), "velocity-x") == 0)
            _object->getPhysicsObject().setVelocityX(_node.text().as_float());
        else if (strcmp(_node.name(), "velocity-y") == 0)
            _object->getPhysicsObject().setVelocityY(_node.text().as_float());
        else if (strcmp(_node.name(), "velocity-z") == 0)
            _object->getPhysicsObject().setVelocityZ(_node.text().as_float());
        else if (strcmp(_node.name(), "elasticity") == 0)
            _object->getPhysicsObject().setElasticity(_node.text().as_float());
        else if (strcmp(_node.name(), "self-collision") == 0)
            _object->getPhysicsObject().setSelfCollision(_node.text().as_bool());
    }
    
    void processXMLPointLightObjectPropertyNode(pugi::xml_node _node, SunPointLightObject *_object) {
        if (strcmp(_node.name(), "position-x") == 0)
            _object->setPositionX(_node.text().as_float());
        else if (strcmp(_node.name(), "position-y") == 0)
            _object->setPositionY(_node.text().as_float());
        else if (strcmp(_node.name(), "position-z") == 0)
            _object->setPositionZ(_node.text().as_float());
        else if (strcmp(_node.name(), "rotation-x") == 0)
            _object->setRotationX(_node.text().as_float());
        else if (strcmp(_node.name(), "rotation-y") == 0)
            _object->setRotationY(_node.text().as_float());
        else if (strcmp(_node.name(), "rotation-z") == 0)
            _object->setRotationZ(_node.text().as_float());
        else if (strcmp(_node.name(), "scale-x") == 0)
            _object->setScaleX(_node.text().as_float());
        else if (strcmp(_node.name(), "scale-y") == 0)
            _object->setScaleY(_node.text().as_float());
        else if (strcmp(_node.name(), "scale-z") == 0)
            _object->setScaleZ(_node.text().as_float());
        else if (strcmp(_node.name(), "color-r") == 0)
            _object->setColorR(_node.text().as_float());
        else if (strcmp(_node.name(), "color-g") == 0)
            _object->setColorG(_node.text().as_float());
        else if (strcmp(_node.name(), "color-b") == 0)
            _object->setColorB(_node.text().as_float());
        else if (strcmp(_node.name(), "pointlightID") == 0)
            _object->setPointLightID(_node.text().as_int());
        else if (strcmp(_node.name(), "attenuate") == 0)
            _object->setAttenuate(_node.text().as_bool());
        else if (strcmp(_node.name(), "physicsenabled") == 0) {
            _object->setPhysicsEnabled(_node.text().as_bool());
            physicsSimulator.getWorld().addObjectToObjects(&_object->getPhysicsObject());
        } else if (strcmp(_node.name(), "stationary") == 0) 
            _object->getPhysicsObject().setStationary(_node.text().as_bool());
        else if (strcmp(_node.name(), "velocity-x") == 0)
            _object->getPhysicsObject().setVelocityX(_node.text().as_float());
        else if (strcmp(_node.name(), "velocity-y") == 0)
            _object->getPhysicsObject().setVelocityY(_node.text().as_float());
        else if (strcmp(_node.name(), "velocity-z") == 0)
            _object->getPhysicsObject().setVelocityZ(_node.text().as_float());
        else if (strcmp(_node.name(), "elasticity") == 0)
            _object->getPhysicsObject().setElasticity(_node.text().as_float());
        else if (strcmp(_node.name(), "self-collision") == 0)
            _object->getPhysicsObject().setSelfCollision(_node.text().as_bool());
    }
    
    void processXMLDirectionalLightObjectPropertyNode(pugi::xml_node _node, SunDirectionalLightObject *_object) {
        if (strcmp(_node.name(), "position-x") == 0)
            _object->setPositionX(_node.text().as_float());
        else if (strcmp(_node.name(), "position-y") == 0)
            _object->setPositionY(_node.text().as_float());
        else if (strcmp(_node.name(), "position-z") == 0)
            _object->setPositionZ(_node.text().as_float());
        else if (strcmp(_node.name(), "rotation-x") == 0)
            _object->setRotationX(_node.text().as_float());
        else if (strcmp(_node.name(), "rotation-y") == 0)
            _object->setRotationY(_node.text().as_float());
        else if (strcmp(_node.name(), "rotation-z") == 0)
            _object->setRotationZ(_node.text().as_float());
        else if (strcmp(_node.name(), "scale-x") == 0)
            _object->setScaleX(_node.text().as_float());
        else if (strcmp(_node.name(), "scale-y") == 0)
            _object->setScaleY(_node.text().as_float());
        else if (strcmp(_node.name(), "scale-z") == 0)
            _object->setScaleZ(_node.text().as_float());
        else if (strcmp(_node.name(), "color-r") == 0)
            _object->setColorR(_node.text().as_float());
        else if (strcmp(_node.name(), "color-g") == 0)
            _object->setColorG(_node.text().as_float());
        else if (strcmp(_node.name(), "color-b") == 0)
            _object->setColorB(_node.text().as_float());
        else if (strcmp(_node.name(), "physicsenabled") == 0) {
            _object->setPhysicsEnabled(_node.text().as_bool());
            physicsSimulator.getWorld().addObjectToObjects(&_object->getPhysicsObject());
        } else if (strcmp(_node.name(), "stationary") == 0) 
            _object->getPhysicsObject().setStationary(_node.text().as_bool());
        else if (strcmp(_node.name(), "velocity-x") == 0)
            _object->getPhysicsObject().setVelocityX(_node.text().as_float());
        else if (strcmp(_node.name(), "velocity-y") == 0)
            _object->getPhysicsObject().setVelocityY(_node.text().as_float());
        else if (strcmp(_node.name(), "velocity-z") == 0)
            _object->getPhysicsObject().setVelocityZ(_node.text().as_float());
        else if (strcmp(_node.name(), "elasticity") == 0)
            _object->getPhysicsObject().setElasticity(_node.text().as_float());
        else if (strcmp(_node.name(), "self-collision") == 0)
            _object->getPhysicsObject().setSelfCollision(_node.text().as_bool());
    }
    
    void cycle(map<int, SunButtonState> _buttons, GLfloat _deltaTime);
    virtual void update(map<int, SunButtonState> _buttons);
    virtual void render(SunNodeSentAction _action);
    void renderGUISystem(SunNodeSentAction _action);
    void passPerFrameUniforms(SunShader _shader);
    void passPerFrameUniforms(SunShader _shader, vector<SunNodeSentActionCondition> _conditions);
    void passPerFrameUniformsAction(SunNodeSentAction _action);
    
    inline SunPhysicsSimulator & getPhysicsSimulator() { return physicsSimulator; }
    
    inline SunGUISystem * getGUISystem() { return GUIsystem; }
    
    inline SunObject * getRootRenderableNode() { return rootRenderableNode; }
    
    inline SunCamera & getCamera() { return camera; }
    inline SunSoundListener & getListener() { return listener; }
    
    inline GLboolean & getDoCameraInput() { return doCameraInput; }
    inline void setDoCameraInput(GLboolean _x) { doCameraInput = _x; }
    
    inline SunRenderer & getRenderer() { return renderer; }
    inline SunTextRenderer & getTextRenderer() { return textRenderer; }
    
    inline int & getPointLightCount() { return pointLightCount; }
    inline void setPointLightCount(int _p) { pointLightCount = _p; }
    
    inline SunSoundBufferStorage & getSoundStorage() { return storage; }
    
    inline SunMusicObject * getMusic() { return music; }
    inline bool & getAutoplay() { return autoplay; }
    inline void setAutoplay(bool _autoplay) { autoplay = _autoplay; }
    
    inline GLFWwindow * getWindow() { return window; }
    inline void setWindow(GLFWwindow *_window) { window = _window; }
private:
    // Physics Simulator
    SunPhysicsSimulator physicsSimulator;
    
    // GUIsystem
    SunGUISystem *GUIsystem;

    // Root renderable node
    SunObject *rootRenderableNode;

    // Camera
    SunCamera camera;
    SunSoundListener listener;
    GLboolean doCameraInput = true;

    // Renderer and Text Renderer
    SunRenderer renderer;
    SunTextRenderer textRenderer;
    
    // Point Light Count
    int pointLightCount;
    
    // Sound Storage
    SunSoundBufferStorage storage;

    // Music
    SunMusicObject *music;
    bool autoplay;

    // Pointer to window
    GLFWwindow *window;
};

#endif
