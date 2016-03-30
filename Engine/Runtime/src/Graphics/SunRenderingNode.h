// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#include <vector>
#include <map>
#include <functional>

#include "SunShader.h"
#include "SunTexturedQuad.h"

class SunWindowManager;

#ifndef SunRenderingNode_h
#define    SunRenderingNode_h

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
    std::string linkName;
    std::string name;

    SunRenderingNodeInput() { }
    SunRenderingNodeInput(SunRenderingNodeOutput *_link, SunRenderingNodeDataType _type, std::string _name, SunRenderingNodeDataFormat _format, SunRenderingNodeTextureType _textureType);
};

class SunRenderingNode : public SunNode {
public:
    SunRenderingNode();
    SunRenderingNode(std::string _name);
    SunRenderingNode(std::string _name, SunRenderingNodeType _renderingType, SunNode *_root);
    SunRenderingNode(std::string _name, SunRenderingNodeType _renderingType, std::vector<SunRenderingNodeInput> _inputs, std::vector<SunRenderingNodeOutput> _outputs);
    SunRenderingNode(std::string _name, SunRenderingNodeType _renderingType, std::vector<SunRenderingNodeInput> _inputs, std::vector<SunRenderingNodeOutput> _outputs, SunNode *_root);

    virtual void init();
    virtual void render(SunAction action);
    void initializeOutput(SunRenderingNodeOutput *_output);

    inline SunRenderingNodeType & getRenderingType() { return renderingType; }
    inline void setRenderingType(SunRenderingNodeType _type) { renderingType = _type; }

    inline std::vector<SunRenderingNodeInput> & getInputs() { return inputs; }
    inline SunRenderingNodeInput & getInputAtIndex(int i) { return inputs[i]; }
    inline void addInputToInputs(SunRenderingNodeInput _input) { inputs.push_back(_input); }
    void setInputs(std::vector<SunRenderingNodeInput> &_inputs) { inputs = _inputs; }

    inline SunRenderingNodeOutput * getOutput(int i) { return outputSlotMap[i]; }
    inline void addOutputToOutputs(SunRenderingNodeOutput output) { outputs.push_back(output); }
    inline void setOutputs(std::vector<SunRenderingNodeOutput> _outputs) { outputs = _outputs; }
    inline void addShaderForString(SunShader shader, std::string string) { shaders.push_back(std::make_pair(string, shader)); }
    inline void setShaders(std::vector<std::pair<std::string, SunShader>> shaders_) { shaders = shaders_; }

    inline void setRoot(SunNode *r) { root = r; }
private:
    SunRenderingNodeType renderingType;
protected:
    // Inputs, Outputs, and Shaders
    std::vector<SunRenderingNodeInput> inputs;
    std::vector<SunRenderingNodeOutput> outputs;
    std::vector<std::pair<std::string, SunShader>> shaders;

    GLuint fbo;
    GLuint rbo;
    std::map<int, SunRenderingNodeOutput *> outputSlotMap;

    SunNode *root;
    static SunTexturedQuad renderQuad;
    static bool quadInitialized;
};

#endif
