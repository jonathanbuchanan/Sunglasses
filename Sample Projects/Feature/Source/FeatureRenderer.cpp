// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureRenderer.h"

void FeatureRenderer::initialize() {
    // GBuffer Inputs
    vector<SunRenderingNodeInput> gbufferInputs = {};
    
    // GBuffer Outputs
    std::vector<SunRenderingNodeOutput> gbufferOutputs;
    gbufferOutputs = {
        SunRenderingNodeOutput(SunRenderingNodeDataTypePosition, SunRenderingNodeDataFormatRGBA16F, 0, glm::vec2(1600, 1200), SunRenderingNodeTextureType2D),
        SunRenderingNodeOutput(SunRenderingNodeDataTypeNormal, SunRenderingNodeDataFormatRGB16F, 1, glm::vec2(1600, 1200), SunRenderingNodeTextureType2D),
        SunRenderingNodeOutput(SunRenderingNodeDataTypeColor, SunRenderingNodeDataFormatRGBA16F, 2, glm::vec2(1600, 1200), SunRenderingNodeTextureType2D)
    };
    gbufferOutputs.push_back(SunRenderingNodeOutput(SunRenderingNodeDataTypePosition, SunRenderingNodeDataFormatRGBA16F, 0, glm::vec2(1600, 1200), SunRenderingNodeTextureType2D));
    
    // GBuffer Shaders
    vector<string> gbufferSources = {"../../Engine/Shaders/Variable Pipeline/Scene.vert", "../../Engine/Shaders/Variable Pipeline/Scene.frag"};
    vector<SunShaderSourceType> gbufferSourceTypes = {SunShaderSourceTypeVertex, SunShaderSourceTypeFragment};
    
    /*map<string, SunRenderingNodeShader> gbufferShaders = {
        {"scene_solid", SunRenderingNodeShader(gbufferSources, gbufferSourceTypes, "../../Engine/Shaders/SolidScene.pre", SunRenderingNodeShaderTypeSceneSolid)},
        {"scene_textured", SunRenderingNodeShader(gbufferSources, gbufferSourceTypes, "../../Engine/Shaders/TexturedScene.pre", SunRenderingNodeShaderTypeSceneTextured)}
    };*/
	// GBuffer Shaders
	std::map<std::string, SunShader> gbufferShaders = {
		{"solid", SunShader("../../Engine/Shaders/Variable Pipeline/Scene.vert", "../../Engine/Shaders/Variable Pipeline/Scene.frag", "../../Engine/Shaders/SolidScene.pre")},
		{"textured", SunShader("../../Engine/Shaders/Variable Pipeline/Scene.vert", "../../Engine/Shaders/Variable Pipeline/Scene.frag", "../../Engine/Shaders/TexturedScene.pre")}
	};
    
    // GBuffer
    SunRenderingNode *gbuffer = new SunRenderingNode("gbuffer", SunRenderingNodeTypeRoot, gbufferInputs, gbufferOutputs, scene->getRoot());
	gbuffer->setShaders(gbufferShaders);
    gbuffer->init();
    gbuffer->setPOVType("camera");
    
    // Set rootRenderNode to GBuffer
    rootRenderNode = gbuffer;
    
    // Final Inputs
    vector<SunRenderingNodeInput> finalInputs = {
        SunRenderingNodeInput(gbuffer, SunRenderingNodeDataTypePosition, "position", SunRenderingNodeDataFormatRGB16F, 0, SunRenderingNodeTextureType2D),
        SunRenderingNodeInput(gbuffer, SunRenderingNodeDataTypeNormal, "normal", SunRenderingNodeDataFormatRGB16F, 1, SunRenderingNodeTextureType2D),
        SunRenderingNodeInput(gbuffer, SunRenderingNodeDataTypeColor, "color", SunRenderingNodeDataFormatRGBA16F, 2, SunRenderingNodeTextureType2D)
    };
    
    // Final Outputs
    vector<SunRenderingNodeOutput> finalOutputs = {
        SunRenderingNodeOutput(SunRenderingNodeDataTypeColor, SunRenderingNodeDataFormatRGBA16F, 0, glm::vec2(1600, 1200), SunRenderingNodeTextureType2D)
    };
    
    // Final Shaders
    vector<string> finalSources = {"../../Engine/Shaders/Variable Pipeline/Quad.vert", "../../Engine/Shaders/Variable Pipeline/Quad.frag"};
    vector<SunShaderSourceType> finalSourceTypes = {SunShaderSourceTypeVertex, SunShaderSourceTypeFragment};
    
    /*map<string, SunRenderingNodeShader> finalShaders = {
        {"quad", SunRenderingNodeShader(finalSources, finalSourceTypes, "../../Engine/Shaders/DeferredQuad.pre", SunRenderingNodeShaderTypeQuad)}
    };*/
    std::map<std::string, SunShader> finalShaders = {
		{"quad", SunShader("../../Engine/Shaders/Variable Pipeline/Scene.vert", "../../Engine/Shaders/Variable Pipeline/Scene.frag", "../../Engine/Shaders/DefferedQuad.pre")}, 
	};
    // Final
    SunRenderingNode *finalNode = new SunRenderingNode("final", SunRenderingNodeTypeEnd, finalInputs, finalOutputs, scene->getRoot());
	finalNode->setShaders(finalShaders);
    finalNode->init();
    gbuffer->addSubNode(finalNode);
}

void FeatureRenderer::render(float delta) {
    SunAction renderAction;
    renderAction.setAction("render");
	renderAction.addParameter("delta", &delta); 
    renderAction.setRecursive(true);

    sendAction(renderAction, rootRenderNode);

	SunAction guiAction("renderGUI");
    
    sendAction(guiAction, (SunBase *)scene);
    
    // Swap the buffers
    swapBuffers();
}
