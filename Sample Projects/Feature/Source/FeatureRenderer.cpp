// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "FeatureRenderer.h"
#include "Extra/SunDirectionalShadowMapRenderingNode.h"

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
	std::vector<std::pair<std::string, SunShader>> gbufferShaders = {
		std::make_pair("solid", SunShader("../../Engine/Shaders/Old/Variable Pipeline/Scene.vert", "../../Engine/Shaders/Old/Variable Pipeline/Scene.frag", "../../Engine/Shaders/Old/SolidScene.pre")),
		std::make_pair("textured", SunShader("../../Engine/Shaders/Old/Variable Pipeline/Scene.vert", "../../Engine/Shaders/Old/Variable Pipeline/Scene.frag", "../../Engine/Shaders/Old/TexturedScene.pre")), 
	};
    
    // GBuffer
    SunRenderingNode *gbuffer = new SunRenderingNode("gbuffer", SunRenderingNodeTypeRoot, gbufferInputs, gbufferOutputs, scene->getRoot());
	gbuffer->setShaders(gbufferShaders);
    gbuffer->init();
	addRenderingNodeForString(gbuffer, "gbuffer");
    
    // Set rootRenderNode to GBuffer
    rootRenderNode = gbuffer;

	// Shadow Map 0
	SunDirectionalShadowMapRenderingNode *shadowMap0 = new SunDirectionalShadowMapRenderingNode(scene->getRoot());
	gbuffer->addSubNode(shadowMap0);
	addRenderingNodeForString(shadowMap0, "shadowMap0");
    
    // Final Inputs
    vector<SunRenderingNodeInput> finalInputs = {
        SunRenderingNodeInput(gbuffer->getOutput(0), SunRenderingNodeDataTypePosition, "position", SunRenderingNodeDataFormatRGB16F, SunRenderingNodeTextureType2D),
        SunRenderingNodeInput(gbuffer->getOutput(1), SunRenderingNodeDataTypeNormal, "normal", SunRenderingNodeDataFormatRGB16F, SunRenderingNodeTextureType2D),
        SunRenderingNodeInput(gbuffer->getOutput(2), SunRenderingNodeDataTypeColor, "color", SunRenderingNodeDataFormatRGBA16F, SunRenderingNodeTextureType2D),
		SunRenderingNodeInput(shadowMap0->getOutput(), SunRenderingNodeDataTypeColor, "shadowMap", SunRenderingNodeDataFormatRGBA16F, SunRenderingNodeTextureType2D)
    };
	
    // Final Outputs
    vector<SunRenderingNodeOutput> finalOutputs = {
        SunRenderingNodeOutput(SunRenderingNodeDataTypeColor, SunRenderingNodeDataFormatRGBA16F, 0, glm::vec2(1600, 1200), SunRenderingNodeTextureType2D)
    };
    
	std::vector<std::pair<std::string, SunShader>> finalShaders = {
		{"quad", SunShader("../../Engine/Shaders/Old/Variable Pipeline/Quad.vert", "../../Engine/Shaders/Old/Variable Pipeline/Quad.frag", "../../Engine/Shaders/Old/DeferredQuad.pre")}, 
	};
    // Final
    SunRenderingNode *finalNode = new SunRenderingNode("final", SunRenderingNodeTypeEnd, finalInputs, finalOutputs, scene->getRoot());
	finalNode->setShaders(finalShaders);
    finalNode->init();
    shadowMap0->addSubNode(finalNode);
	addRenderingNodeForString(finalNode, "final");
} 
