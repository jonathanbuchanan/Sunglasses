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
    inline void setRenderingType(SunRenderingNodeType _type) { renderingType = _type; } 
    
    inline vector<SunRenderingNodeInput> & getInputs() { return inputs; }
    inline SunRenderingNodeInput & getInputAtIndex(int i) { return inputs[i]; }
    inline void addInputToInputs(SunRenderingNodeInput _input) { inputs.push_back(_input); }
    void setInputs(vector<SunRenderingNodeInput> &_inputs) { inputs = _inputs; }
    
    inline vector<SunRenderingNodeOutput> & getOutputs() { return outputs; }
    inline SunRenderingNodeOutput & getOutputAtIndex(int i) { return outputs[i]; }
    inline void addOutputToOutputs(SunRenderingNodeOutput output) { outputs.push_back(output); }
    inline void setOutputs(vector<SunRenderingNodeOutput> _outputs) { outputs = _outputs; }
   
	inline void addShaderForString(SunShader shader, std::string string) { shaders.push_back(std::make_pair(string, shader)); }
	inline void setShaders(std::vector<std::pair<std::string, SunShader>> shaders_) { shaders = shaders_; }

    inline void setRoot(SunNode *r) { root = r; } 
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
