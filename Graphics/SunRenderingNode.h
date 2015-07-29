/* 
 * File:   SunRenderingNode.h
 * Author: jonathan
 *
 * Created on July 17, 2015, 12:39 AM
 */

#include <vector>
#include <map>
#include <functional>

#include "../SunNode.h"
#include "./Shaders/SunShader.h"
#include "../SunObject.h"
#include "./SunTexturedQuad.h"
#include "./Shaders/SunShaderUniformObject.h"

#ifndef SunRenderingNode_h
#define	SunRenderingNode_h

using namespace std;

class SunRenderingNode;

typedef SunRenderingNode * SunRenderingNodePointer;

enum SunRenderingNodeType {
    SunRenderingNodeTypeRoot,
    SunRenderingNodeTypeIntermediate,
    SunRenderingNodeTypeEnd,
    SunRenderingNodeTypeOnly
};

enum SunRenderingNodeDataType {
    SunRenderingNodeDataTypeColor,
    SunRenderingNodeDataTypePosition,
    SunRenderingNodeDataTypeNormal,
    SunRenderingNodeDataTypeOcclusion
};

enum SunRenderingNodeDataFormat {
    SunRenderingNodeDataFormatRGB16F,
    SunRenderingNodeDataFormatRGBA16F,
    SunRenderingNodeDataFormat16F
};

struct SunRenderingNodeOutput {
    SunRenderingNodeDataType type;
    SunRenderingNodeDataFormat format;
    int slot;
    GLuint texture;
};

struct SunRenderingNodeInput {
    SunRenderingNodeDataType type;
    SunRenderingNodeDataFormat format;
    int slot;
    SunRenderingNodePointer link;
    string linkName;
    string name;
};

enum SunRenderingNodeShaderType {
    SunRenderingNodeShaderTypeSceneTextured,
    SunRenderingNodeShaderTypeSceneSolid,
    SunRenderingNodeShaderTypeQuad
};

class SunRenderingNodeShader : public SunNode {
public:
    SunShader shader;
    SunRenderingNodeShaderType shaderType;
    SunNodeSentAction action;
    
    SunRenderingNodeShader() {
        
    }
    
    SunRenderingNodeShader(string _vertexSource, string _fragmentSource, string _preprocessorSource, SunRenderingNodeShaderType _type) {
        string hi = "hi";
        shader = SunShader(_vertexSource.c_str(), _fragmentSource.c_str(), _preprocessorSource.c_str(), hi.c_str());
        
        action.action = "render";
        action.parameters["shader"] = &shader;
        action.recursive = true;
        
        SunNodeSentActionCondition condition;
        condition.conditionType = SunNodeSentActionConditionTypeEqualTo;
        condition.nodeProperty = "renderType";
        if (_type == SunRenderingNodeShaderTypeSceneTextured) {
            SunMeshRenderType renderType = SunMeshRenderTypeTextured;
            condition.comparativeProperty = SunNodeProperty(&renderType, SunNodePropertyTypeInt);
        } else if (_type == SunRenderingNodeShaderTypeSceneSolid) {
            SunMeshRenderType renderType = SunMeshRenderTypeSolid;
            condition.comparativeProperty = SunNodeProperty(&renderType, SunNodePropertyTypeInt);
        }
        
        action.conditions.push_back(condition);
        
        shaderType = _type;
    }
private:
    
};

class SunRenderingNode : public SunNode {
public:
    SunRenderingNodeType type;
    vector<SunRenderingNodeInput> inputs;
    vector<SunRenderingNodeOutput> outputs;
    SunFramebuffer outputFramebuffer;
    map<int, SunRenderingNodeOutput *> outputSlotMap;
    map<string, SunRenderingNodeShader> shaders;
    vector<SunTexture> textures;
    vector<SunShaderUniformObject *> uniforms;
    
    SunNode *scene;
    SunTexturedQuad renderQuad;
    
    SunRenderingNode() {
        initializeDefaultPropertyAndFunctionMap();
    }
    
    SunRenderingNode(string _name) {
        name = _name;
        
        initializeDefaultPropertyAndFunctionMap();
    }
    
    virtual void initializeDefaultPropertyAndFunctionMap() {
        SunNode::initializeDefaultPropertyAndFunctionMap();
        
        functionMap["render"] = bind(&SunRenderingNode::render, this, std::placeholders::_1);
    }
    
    void render(SunNodeSentAction _action) {
        GLfloat _deltaTime = *(GLfloat *)_action.parameters["deltaTime"];
        if (type == SunRenderingNodeTypeRoot) {
            clear();
            
            // Bind the framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, outputFramebuffer.framebuffer);

            // Clear
            clear();

            // Tell the scene to render with the shaders
            SunNodeSentAction renderAction;
            renderAction.action = "render";
            
            map<string, SunShader> _shaders;
            for (map<string, SunRenderingNodeShader>::iterator iterator = shaders.begin(); iterator != shaders.end(); iterator++) {
                SunRenderingNodeShader shader = iterator->second;
                _shaders[iterator->first] = shader.shader;
            }
            
            renderAction.parameters["shaderMap"] = &_shaders;
            renderAction.parameters["deltaTime"] = &_deltaTime;

            sendAction(renderAction, scene);
        } else if (type == SunRenderingNodeTypeIntermediate) {
            // Get the input textures
            map<string, GLuint> _textures;
            for (int i = 0; i < inputs.size(); i++) {
                _textures[inputs[i].name] = inputs[i].link->outputSlotMap[inputs[i].slot]->texture;
            }
            
            for (int i = 0; i < textures.size(); i++) {
                _textures[textures[i].name] = textures[i].id;
            }

            // Bind the framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, outputFramebuffer.framebuffer);
            clear();

            shaders["quad"].shader.use();
            
            glm::mat4 matrix;
            matrix = glm::perspective(45.0f, 800.0f / 600.0f, 0.01f, 100.0f);
            
            GLint projectionMatrixLocation = glGetUniformLocation(shaders["quad"].shader.program, "projection");
            glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));

            passUniforms(&shaders["quad"].shader);

            renderQuad.renderWithUsedShader(_textures, shaders["quad"].shader);
        } else if (type == SunRenderingNodeTypeEnd) {
            // Get a pointer to the input framebuffer
            map<string, GLuint> _textures;
            for (int i = 0; i < inputs.size(); i++) {
                _textures[inputs[i].name] = inputs[i].link->outputSlotMap[inputs[i].slot]->texture;
            }
            
            for (int i = 0; i < textures.size(); i++) {
                _textures[textures[i].name] = textures[i].id;
            }

            // Bind the screen-framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            clear();

            shaders["quad"].shader.use();

            passUniforms(&shaders["quad"].shader);

            renderQuad.renderWithUsedShader(_textures, shaders["quad"].shader);
        } else if (type == SunRenderingNodeTypeOnly) {
            // Bind the screen-framebuffer
            clear();
            
            // Bind the framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // Clear
            clear();

            // Tell the scene to render with the shaders
            SunNodeSentAction renderAction;
            renderAction.action = "render";
            
            map<string, SunShader> _shaders;
            for (map<string, SunRenderingNodeShader>::iterator iterator = shaders.begin(); iterator != shaders.end(); iterator++) {
                SunRenderingNodeShader shader = iterator->second;
                _shaders[iterator->first] = shader.shader;
            }
            
            renderAction.parameters["shaderMap"] = &_shaders;
            renderAction.parameters["deltaTime"] = &_deltaTime;

            sendAction(renderAction, scene);
        }
    }
    
    void passUniforms(SunShader *_shader) {
        SunNodeSentAction uniformAction;
        uniformAction.action = "passPerFrameUniforms";
        uniformAction.parameters["shader"] = _shader;
        
        SunNodeSentActionCondition condition;
        condition.nodeProperty = "type";
        condition.comparativeProperty = SunNodeProperty(new string("light"), SunNodePropertyTypeString);
        condition.conditionType = SunNodeSentActionConditionTypeEqualTo;

        vector<SunNodeSentActionCondition> conditions;
        conditions.push_back(condition);

        uniformAction.parameters["conditions"] = &conditions;
        
        sendAction(uniformAction, scene);
        
        SunNodeSentAction _uniformAction;
        _uniformAction.action = "passUniform";
        _uniformAction.parameters["shader"] = _shader;
        
        for (int i = 0; i < uniforms.size(); i++)
            sendAction(_uniformAction, uniforms[i]);
    }
    
    void initialize() {
        // Create the framebuffer
        if (type == SunRenderingNodeTypeRoot) {
            glGenFramebuffers(1, &outputFramebuffer.framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, outputFramebuffer.framebuffer);
            
            for (int i = 0; i < outputs.size(); i++) {
                initializeOutput(&outputs[i]);
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            
            glGenRenderbuffers(1, &outputFramebuffer.renderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, outputFramebuffer.renderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1600, 1200);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, outputFramebuffer.renderbuffer);
            
            GLuint colorAttachments[outputs.size()];
            
            for (int i = 0; i < outputs.size(); i++)
                colorAttachments[i] = GL_COLOR_ATTACHMENT0 + i;
            
            glDrawBuffers(outputs.size(), colorAttachments);
            
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Frame buffer not complete!" << std::endl;
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        } else if (type == SunRenderingNodeTypeIntermediate) {
            glGenFramebuffers(1, &outputFramebuffer.framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, outputFramebuffer.framebuffer);
            
            for (int i = 0; i < outputs.size(); i++) {
                initializeOutput(&outputs[i]);
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            
            glGenRenderbuffers(1, &outputFramebuffer.renderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, outputFramebuffer.renderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1600, 1200);

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, outputFramebuffer.renderbuffer);
            
            GLuint colorAttachments[outputs.size()];
            
            for (int i = 0; i < outputs.size(); i++)
                colorAttachments[i] = GL_COLOR_ATTACHMENT0 + i;
            
            glDrawBuffers(2, colorAttachments);
            
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "Frame buffer not complete!" << std::endl;
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            
            // Initialize the quad
            renderQuad = SunTexturedQuad();
            renderQuad.setUpGL();
        } else if (type == SunRenderingNodeTypeEnd) {
            // Initialize the quad
            renderQuad = SunTexturedQuad();
            renderQuad.setUpGL();
        }
    }
    
    void initializeOutput(SunRenderingNodeOutput *_output) {
        glGenTextures(1, &_output->texture);

        glBindFramebuffer(GL_FRAMEBUFFER, outputFramebuffer.framebuffer);
        glBindTexture(GL_TEXTURE_2D, _output->texture);
        
        if (_output->format == SunRenderingNodeDataFormatRGB16F)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 1600, 1200, 0, GL_RGB, GL_FLOAT, NULL);
        else if (_output->format == SunRenderingNodeDataFormatRGBA16F)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1600, 1200, 0, GL_RGBA, GL_FLOAT, NULL);
        else if (_output->format == SunRenderingNodeDataFormat16F)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, 1600, 1200, 0, GL_RED, GL_FLOAT, NULL);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _output->slot, GL_TEXTURE_2D, _output->texture, 0);
        outputSlotMap[_output->slot] = _output;
    }
    
private:
    
};

#endif

