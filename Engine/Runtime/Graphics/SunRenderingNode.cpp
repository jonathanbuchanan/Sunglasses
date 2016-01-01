// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunRenderingNode.h"

SunRenderingNode::SunRenderingNode() {
    initializeDefaultPropertyAndFunctionMap();
}

SunRenderingNode::SunRenderingNode(string _name) {
    setName(_name);

    initializeDefaultPropertyAndFunctionMap();
}

void SunRenderingNode::initializeDefaultPropertyAndFunctionMap() {
    SunNode::initializeDefaultPropertyAndFunctionMap();

    addToFunctionMap("render", bind(&SunRenderingNode::render, this, std::placeholders::_1));
    addToFunctionMap("test", bind(&SunRenderingNode::test, this, std::placeholders::_1));
}

void SunRenderingNode::test(SunNodeSentAction _action) {
	cout << "Name: " + this->getName() + ", Parents: " << endl;
	for (int i = 0; i < this->getParentsSize(); i++) {
		cout << "	" + this->getParentAtIndex(i)->getName() << endl;
	}
	cout << "Children: " << endl;
	for (int i = 0; i < this->getSubNodesSize(); i++) {
		cout << "	" + this->getSubNodeAtIndex(i)->getName() << endl;
	}
}

void SunRenderingNode::render(SunNodeSentAction _action) {
    GLfloat _deltaTime = *(GLfloat *)_action.parameters["deltaTime"];
    if (renderingType == SunRenderingNodeTypeRoot) {
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
        renderAction.parameters["POVtype"] = &POVtype;
        renderAction.parameters["POV"] = &POV;

        sendAction(renderAction, scene);
    } else if (renderingType == SunRenderingNodeTypeIntermediate) {
        // Get the input textures
        map<string, pair<GLuint, GLuint>> _textures;
        for (int i = 0; i < inputs.size(); i++) {
            if (inputs[i].textureType == SunRenderingNodeTextureType2D)
                _textures[inputs[i].name] = make_pair(inputs[i].link->outputSlotMap[inputs[i].slot]->texture, GL_TEXTURE_2D);
            else if (inputs[i].textureType == SunRenderingNodeTextureTypeCubemap)
                _textures[inputs[i].name] = make_pair(inputs[i].link->outputSlotMap[inputs[i].slot]->texture, GL_TEXTURE_CUBE_MAP);
        }

        for (int i = 0; i < textures.size(); i++) {
            _textures[textures[i].name] = make_pair(textures[i].id, GL_TEXTURE_2D);
        }

        // Bind the framebuffer
        glViewport(0, 0, 1024, 1024);
        glBindFramebuffer(GL_FRAMEBUFFER, outputFramebuffer.framebuffer);
        clear();
        //glClear(GL_DEPTH_BUFFER_BIT);
        
        if (shaderType == SunRenderingNodeShaderTypeScene) {
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
            renderAction.parameters["POVtype"] = &POVtype;
            renderAction.parameters["POV"] = &POV;

            sendAction(renderAction, scene);
        } else if (shaderType == SunRenderingNodeShaderTypeQuad) {
            shaders["quad"].shader.use();

            passUniforms(&shaders["quad"].shader, textures.size());

            renderQuad.renderWithUsedShader(_textures, shaders["quad"].shader);
        }
        glViewport(0, 0, screenWidth, screenHeight);
    } else if (renderingType == SunRenderingNodeTypeEnd) {
        // Get a pointer to the input framebuffer
        map<string, pair<GLuint, GLuint>> _textures;
        for (int i = 0; i < inputs.size(); i++) {
            if (inputs[i].textureType == SunRenderingNodeTextureType2D)
                _textures[inputs[i].name] = make_pair(inputs[i].link->outputSlotMap[inputs[i].slot]->texture, GL_TEXTURE_2D);
            else if (inputs[i].textureType == SunRenderingNodeTextureTypeCubemap)
                _textures[inputs[i].name] = make_pair(inputs[i].link->outputSlotMap[inputs[i].slot]->texture, GL_TEXTURE_CUBE_MAP);
        }

        for (int i = 0; i < textures.size(); i++) {
            _textures[textures[i].name] = make_pair(textures[i].id, GL_TEXTURE_2D);
        }

        // Bind the screen-framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        clear();
		
		glViewport(0, 0, screenWidth * 2, screenHeight * 2);
		
        shaders["quad"].shader.use();
		
        passUniforms(&shaders["quad"].shader, inputs.size());

        renderQuad.renderWithUsedShader(_textures, shaders["quad"].shader);
		
		glViewport(0, 0, screenWidth, screenHeight);
    } else if (renderingType == SunRenderingNodeTypeOnly) {
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

void SunRenderingNode::passUniforms(SunShader *_shader) {
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

void SunRenderingNode::passUniforms(SunShader *_shader, int textureUnits) {
    SunNodeSentAction uniformAction;
    uniformAction.action = "passPerFrameUniforms";
    uniformAction.parameters["shader"] = _shader;
	uniformAction.parameters["usedTextureUnits"] = &textureUnits;

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

void SunRenderingNode::initialize() {
    // Create the framebuffer
    if (renderingType == SunRenderingNodeTypeRoot) {
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
    } else if (renderingType == SunRenderingNodeTypeIntermediate) {
        glGenFramebuffers(1, &outputFramebuffer.framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, outputFramebuffer.framebuffer);

        for (int i = 0; i < outputs.size(); i++) {
            initializeOutput(&outputs[i]);
        }

        //glGenRenderbuffers(1, &outputFramebuffer.renderbuffer);
        //glBindRenderbuffer(GL_RENDERBUFFER, outputFramebuffer.renderbuffer);
        //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth, screenHeight);

        //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, outputFramebuffer.renderbuffer);

        //GLuint colorAttachments[outputs.size()];

        //for (int i = 0; i < outputs.size(); i++)
        //    colorAttachments[i] = GL_COLOR_ATTACHMENT0 + i;


        //glDrawBuffers(outputs.size(), colorAttachments);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Frame buffer (" + this->getName() + ") not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Initialize the quad
        renderQuad = SunTexturedQuad();
        renderQuad.setUpGL();
    } else if (renderingType == SunRenderingNodeTypeEnd) {
        // Initialize the quad
        renderQuad = SunTexturedQuad();
        renderQuad.setUpGL();
    }
}

void SunRenderingNode::initializeOutput(SunRenderingNodeOutput *_output) {
    glGenTextures(1, &_output->texture);

    glBindFramebuffer(GL_FRAMEBUFFER, outputFramebuffer.framebuffer);
    
    if (_output->textureType == SunRenderingNodeTextureType2D) {
        glBindTexture(GL_TEXTURE_2D, _output->texture);
        if (_output->format == SunRenderingNodeDataFormatRGB16F)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, _output->size.x, _output->size.y, 0, GL_RGB, GL_FLOAT, NULL);
        else if (_output->format == SunRenderingNodeDataFormatRGBA16F)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _output->size.x, _output->size.y, 0, GL_RGBA, GL_FLOAT, NULL);
        else if (_output->format == SunRenderingNodeDataFormat16F)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, _output->size.x, _output->size.y, 0, GL_RED, GL_FLOAT, NULL);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _output->slot, GL_TEXTURE_2D, _output->texture, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    } else if (_output->textureType == SunRenderingNodeTextureTypeCubemap) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _output->texture);
        
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        
        if (_output->format == SunRenderingNodeDataFormatRGB16F) {
            for (int i = 0; i < 6; i++)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, _output->size.x, _output->size.y, 0, GL_RGB, GL_FLOAT, NULL);
        } else if (_output->format == SunRenderingNodeDataFormatRGBA16F) {
            for (int i = 0; i < 6; i++)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16F, _output->size.x, _output->size.y, 0, GL_RGBA, GL_FLOAT, NULL);
        } else if (_output->format == SunRenderingNodeDataFormat16F) {
            for (int i = 0; i < 6; i++)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, _output->size.x, _output->size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        }
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _output->texture, 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    outputSlotMap[_output->slot] = _output;
}

