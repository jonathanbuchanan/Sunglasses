// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#include <vector>
#include <map>
#include <functional>

#include "Graphics/SunShader.h"
#include "SunObject.h"
#include "./SunTexturedQuad.h" 
#include "SunGame.h"

#ifndef SunRenderingNode_h
#define	SunRenderingNode_h

using namespace std;

class SunRenderingNode;

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
    SunRenderingNodeOutput *output;
    SunRenderingNodeTextureType textureType;
	string linkName;
    string name;
    
    SunRenderingNodeInput() { }
    SunRenderingNodeInput(SunRenderingNodeOutput *_link, SunRenderingNodeDataType _type, string _name, SunRenderingNodeDataFormat _format, SunRenderingNodeTextureType _textureType);
};

class SunRenderingNode : public SunNode {
public:
    SunRenderingNode();
    SunRenderingNode(string _name);
    SunRenderingNode(string _name, SunRenderingNodeType _renderingType, SunNode *_root);
    SunRenderingNode(string _name, SunRenderingNodeType _renderingType, vector<SunRenderingNodeInput> _inputs, vector<SunRenderingNodeOutput> _outputs);
    SunRenderingNode(string _name, SunRenderingNodeType _renderingType, vector<SunRenderingNodeInput> _inputs, vector<SunRenderingNodeOutput> _outputs, SunNode *_root);
    
    virtual void init();
    virtual void render(SunAction action);
	void initializeOutput(SunRenderingNodeOutput *_output);
    
    inline SunRenderingNodeType & getRenderingType() { return renderingType; }
<<<<<<< HEAD
    inline void setRenderingType(SunRenderingNodeType _type) { renderingType = _type; }
    
    inline SunRenderingNodeShaderType & getShaderType() { return shaderType; }
    inline void setShaderType(SunRenderingNodeShaderType _type) { shaderType = _type; }
    
=======
    inline void setRenderingType(SunRenderingNodeType _type) { renderingType = _type; } 
>>>>>>> render
    
    inline vector<SunRenderingNodeInput> & getInputs() { return inputs; }
    inline SunRenderingNodeInput & getInputAtIndex(int i) { return inputs[i]; }
    inline void addInputToInputs(SunRenderingNodeInput _input) { inputs.push_back(_input); }
    void setInputs(vector<SunRenderingNodeInput> &_inputs) { inputs = _inputs; }
    
    inline SunRenderingNodeOutput * getOutput(int i) { return outputSlotMap[i]; }
    inline void addOutputToOutputs(SunRenderingNodeOutput output) { outputs.push_back(output); }
    inline void setOutputs(vector<SunRenderingNodeOutput> _outputs) { outputs = _outputs; }
<<<<<<< HEAD
    
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
=======
   
	inline void addShaderForString(SunShader shader, std::string string) { shaders.push_back(std::make_pair(string, shader)); }
	inline void setShaders(std::vector<std::pair<std::string, SunShader>> shaders_) { shaders = shaders_; }

    inline void setRoot(SunNode *r) { root = r; } 
>>>>>>> render
private:
    SunRenderingNodeType renderingType; 
protected:
    // Inputs, Outputs, and Shaders
    vector<SunRenderingNodeInput> inputs;
    vector<SunRenderingNodeOutput> outputs;
	std::vector<std::pair<std::string, SunShader>> shaders;
    
	GLuint fbo;
	GLuint rbo;
    map<int, SunRenderingNodeOutput *> outputSlotMap; 

    SunNode *root;
    static SunTexturedQuad renderQuad;
	static bool quadInitialized;
};

#endif 
