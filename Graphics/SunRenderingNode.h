/* 
 * File:   SunRenderingNode.h
 * Author: jonathan
 *
 * Created on July 17, 2015, 12:39 AM
 */

#include <vector>
#include <map>
#include <functional>

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
    SunRenderingNode();
    SunRenderingNode(string _name);
    
    virtual void initializeDefaultPropertyAndFunctionMap();
    void render(SunNodeSentAction _action);
    void passUniforms(SunShader *_shader);
    void initialize();
    void initializeOutput(SunRenderingNodeOutput *_output);
    
    inline SunRenderingNodeType & getRenderingType() { return renderingType; }
    inline void setRenderingType(SunRenderingNodeType _type) { renderingType = _type; }
    
    inline vector<SunRenderingNodeInput> & getInputs() { return inputs; }
    inline SunRenderingNodeInput & getInputAtIndex(int i) { return inputs[i]; }
    inline void addInputToInputs(SunRenderingNodeInput _input) { inputs.push_back(_input); }
    
    inline vector<SunRenderingNodeOutput> & getOutputs() { return outputs; }
    inline SunRenderingNodeOutput & getOutputAtIndex(int i) { return outputs[i]; }
    inline void addOutputToOutputs(SunRenderingNodeOutput output) { outputs.push_back(output); }
    
    inline SunFramebuffer & getFramebuffer() { return outputFramebuffer; }
    
    inline map<string, SunRenderingNodeShader> & getShaders() { return shaders; }
    inline SunRenderingNodeShader & getShaderForString(string s) { return shaders[s]; }
    inline void addShaderForString(string s, SunRenderingNodeShader shader) { shaders[s] = shader; }
    
    inline vector<SunTexture> & getTextures() { return textures; }
    inline SunTexture & getTextureAtIndex(int i) { return textures[i]; }
    inline void addTextureToTextures(SunTexture t) { textures.push_back(t); }
    
    inline vector<SunShaderUniformObject *> getUniforms() { return uniforms; }
    inline SunShaderUniformObject * getUniformAtIndex(int i) { return uniforms[i]; }
    inline void addUniformToUniforms(SunShaderUniformObject *u) { uniforms.push_back(u); }
    
    inline SunNode * getSceneNode() { return scene; }
    inline void setSceneNode(SunNode *_scene) { scene = _scene; }
    
    inline SunTexturedQuad & getQuad() { return renderQuad; }
private:
    SunRenderingNodeType renderingType;
    vector<SunRenderingNodeInput> inputs;
    vector<SunRenderingNodeOutput> outputs;
    SunFramebuffer outputFramebuffer;
    map<int, SunRenderingNodeOutput *> outputSlotMap;
    map<string, SunRenderingNodeShader> shaders;
    vector<SunTexture> textures;
    vector<SunShaderUniformObject *> uniforms;

    SunNode *scene;
    SunTexturedQuad renderQuad;
};

#endif

