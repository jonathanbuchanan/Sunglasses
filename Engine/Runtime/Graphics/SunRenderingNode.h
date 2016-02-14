// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#include <vector>
#include <map>
#include <functional>

#include "./Shaders/SunShader.h"
#include "SunObject.h"
#include "./SunTexturedQuad.h"
#include "./Shaders/SunShaderUniformObject.h"
#include "SunGame.h"

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
    SunRenderingNodeDataTypeOcclusion,
    SunRenderingNodeDataTypeDepth
};

enum SunRenderingNodeDataFormat {
    SunRenderingNodeDataFormatRGB16F,
    SunRenderingNodeDataFormatRGBA16F,
    SunRenderingNodeDataFormat16F
};

enum SunRenderingNodeTextureType {
    SunRenderingNodeTextureType2D,
    SunRenderingNodeTextureTypeCubemap
};

struct SunRenderingNodeOutput {
    SunRenderingNodeDataType type;
    SunRenderingNodeDataFormat format;
    int slot;
    glm::vec2 size;
    SunRenderingNodeTextureType textureType;
    GLuint texture;
    
    SunRenderingNodeOutput() { }
    SunRenderingNodeOutput(SunRenderingNodeDataType _type, SunRenderingNodeDataFormat _format, int _slot, glm::vec2 _size, SunRenderingNodeTextureType _textureType);
};

struct SunRenderingNodeInput {
    SunRenderingNodeDataType type;
    SunRenderingNodeDataFormat format;
    int slot;
    SunRenderingNodePointer link;
    SunRenderingNodeTextureType textureType;
    string linkName;
    string name;
    
    SunRenderingNodeInput() { }
    SunRenderingNodeInput(SunRenderingNodePointer _link, SunRenderingNodeDataType _type, string _name, SunRenderingNodeDataFormat _format, int _slot, SunRenderingNodeTextureType _textureType);
};

enum SunRenderingNodeShaderType {
    SunRenderingNodeShaderTypeSceneTextured,
    SunRenderingNodeShaderTypeSceneSolid,
    SunRenderingNodeShaderTypeScene,
    SunRenderingNodeShaderTypeQuad
};

class SunRenderingNodeShader : public SunNode {
public:
    SunShader shader;
    SunRenderingNodeShaderType shaderType;
    SunAction action;
    
    SunRenderingNodeShader() {
        
    }
    
    SunRenderingNodeShader(string _vertexSource, string _fragmentSource, string _preprocessorSource, SunRenderingNodeShaderType _type) {
        string hi = "hi";
        shader = SunShader(_vertexSource.c_str(), _fragmentSource.c_str(), _preprocessorSource.c_str(), hi.c_str());
        
        action.setAction("render");
        action.addParameter("shader", &shader);
        action.setRecursive(true);
        
        /*SunNodeSentActionCondition condition;
        condition.conditionType = SunNodeSentActionConditionTypeEqualTo;
        condition.nodeProperty = "renderType";
        if (_type == SunRenderingNodeShaderTypeSceneTextured) {
            SunMeshRenderType renderType = SunMeshRenderTypeTextured;
            condition.comparativeProperty = SunNodeProperty(&renderType, SunNodePropertyTypeInt);
        } else if (_type == SunRenderingNodeShaderTypeSceneSolid) {
            SunMeshRenderType renderType = SunMeshRenderTypeSolid;
            condition.comparativeProperty = SunNodeProperty(&renderType, SunNodePropertyTypeInt);
        }
        
        action.conditions.push_back(condition);*/
        
        shaderType = _type;
    }
    
    SunRenderingNodeShader(vector<string> sources, vector<SunShaderSourceType> sourceTypes, string preprocessorPath, SunRenderingNodeShaderType _type) {
        shader = SunShader(sources, sourceTypes, preprocessorPath);
        
		action.setAction("render");
		action.addParameter("shader", &shader);
		action.setRecursive(true); 
        
        /*SunNodeSentActionCondition condition;
        condition.conditionType = SunNodeSentActionConditionTypeEqualTo;
        condition.nodeProperty = "renderType";
        if (_type == SunRenderingNodeShaderTypeSceneTextured) {
            SunMeshRenderType renderType = SunMeshRenderTypeTextured;
            condition.comparativeProperty = SunNodeProperty(&renderType, SunNodePropertyTypeInt);
        } else if (_type == SunRenderingNodeShaderTypeSceneSolid) {
            SunMeshRenderType renderType = SunMeshRenderTypeSolid;
     		condition.comparativeProperty = SunNodeProperty(&renderType, SunNodePropertyTypeInt);
        }
        
        action.conditions.push_back(condition);*/
        
        shaderType = _type;
    }
private:
    
};

class SunRenderingNode : public SunNode {
public:
    SunRenderingNode();
    SunRenderingNode(string _name);
    SunRenderingNode(string _name, SunRenderingNodeType _renderingType, SunNode *_scene);
    SunRenderingNode(string _name, SunRenderingNodeType _renderingType, vector<SunRenderingNodeInput> _inputs, vector<SunRenderingNodeOutput> _outputs, map<string, SunRenderingNodeShader> _shaders);
    SunRenderingNode(string _name, SunRenderingNodeType _renderingType, vector<SunRenderingNodeInput> _inputs, vector<SunRenderingNodeOutput> _outputs, map<string, SunRenderingNodeShader> _shaders, SunNode *_scene);
    
    virtual void init();
    virtual void render(SunAction action);
    void passUniforms(SunShader *_shader);
	void passUniforms(SunShader *_shader, int textureUnits);
    void initializeOutput(SunRenderingNodeOutput *_output);
    
    inline SunRenderingNodeType & getRenderingType() { return renderingType; }
    inline void setRenderingType(SunRenderingNodeType _type) { renderingType = _type; }
    
    inline SunRenderingNodeShaderType & getShaderType() { return shaderType; }
    inline void setShaderType(SunRenderingNodeShaderType _type) { shaderType = _type; } 
    
    inline vector<SunRenderingNodeInput> & getInputs() { return inputs; }
    inline SunRenderingNodeInput & getInputAtIndex(int i) { return inputs[i]; }
    inline void addInputToInputs(SunRenderingNodeInput _input) { inputs.push_back(_input); }
    void setInputs(vector<SunRenderingNodeInput> &_inputs) { inputs = _inputs; }
    
    inline vector<SunRenderingNodeOutput> & getOutputs() { return outputs; }
    inline SunRenderingNodeOutput & getOutputAtIndex(int i) { return outputs[i]; }
    inline void addOutputToOutputs(SunRenderingNodeOutput output) { outputs.push_back(output); }
    inline void setOutputs(vector<SunRenderingNodeOutput> _outputs) { outputs = _outputs; }
    
    inline map<string, SunRenderingNodeShader> & getShaders() { return shaders; }
    inline SunRenderingNodeShader & getShaderForString(string s) { return shaders[s]; }
    inline void addShaderForString(string s, SunRenderingNodeShader shader) { shaders[s] = shader; }
    inline void setShaders(map<string, SunRenderingNodeShader> _shaders) { shaders = _shaders; }
    
    inline SunFramebuffer & getFramebuffer() { return outputFramebuffer; }
    
    inline vector<SunTexture> & getTextures() { return textures; }
    inline SunTexture & getTextureAtIndex(int i) { return textures[i]; }
    inline void addTextureToTextures(SunTexture t) { textures.push_back(t); }
    
    inline vector<SunShaderUniformObject *> getUniforms() { return uniforms; }
    inline SunShaderUniformObject * getUniformAtIndex(int i) { return uniforms[i]; }
    inline void addUniformToUniforms(SunShaderUniformObject *u) { uniforms.push_back(u); }
    
    inline string & getPOVType() { return POVtype; }
    inline void setPOVType(string _p) { POVtype = _p; }
    
    inline string & getPOV() { return POV; }
    inline void setPOV(string _p) { POV = _p; }
    
    inline SunNode * getSceneNode() { return scene; }
    inline void setSceneNode(SunNode *_scene) { scene = _scene; }
    
    inline SunTexturedQuad & getQuad() { return renderQuad; }
private:
    SunRenderingNodeType renderingType;
    SunRenderingNodeShaderType shaderType;
protected:
    // Inputs, Outputs, and Shaders
    vector<SunRenderingNodeInput> inputs;
    vector<SunRenderingNodeOutput> outputs;
    map<string, SunRenderingNodeShader> shaders;
    
    SunFramebuffer outputFramebuffer;
    map<int, SunRenderingNodeOutput *> outputSlotMap;
    vector<SunTexture> textures;
    vector<SunShaderUniformObject *> uniforms;
    string POVtype;
    string POV;

    SunNode *scene;
    SunTexturedQuad renderQuad;
};

#endif

