#include "FeatureRenderer.h"

void FeatureRenderer::initialize() {
	// GBuffer Inputs
	vector<SunRenderingNodeInput> gbufferInputs;
	
	// GBuffer Outputs
	vector<SunRenderingNodeOutput> gbufferOutputs = {
		SunRenderingNodeOutput(SunRenderingNodeDataTypePosition, SunRenderingNodeDataFormatRGBA16F, 0, glm::vec2(1600, 1200), SunRenderingNodeTextureType2D),
		SunRenderingNodeOutput(SunRenderingNodeDataTypeNormal, SunRenderingNodeDataFormatRGB16F, 1, glm::vec2(1600, 1200), SunRenderingNodeTextureType2D),
		SunRenderingNodeOutput(SunRenderingNodeDataTypeColor, SunRenderingNodeDataFormatRGBA16F, 2, glm::vec2(1600, 1200), SunRenderingNodeTextureType2D)
	};
	
	// GBuffer Shaders
	vector<string> sources = {"../../Engine/Shaders/Variable Pipeline/Scene.vert", "../../Engine/Shaders/Variable Pipeline/Scene.frag"};
	vector<SunShaderSourceType> sourceTypes = {SunShaderSourceTypeVertex, SunShaderSourceTypeFragment};
	
	
	map<string, SunRenderingNodeShader> gbufferShaders = {
		{"scene_solid", SunRenderingNodeShader(sources, sourceTypes, "../../Engine/Shaders/SolidScene.pre", SunRenderingNodeShaderTypeSceneSolid)},
		{"scene_textured", SunRenderingNodeShader(sources, sourceTypes, "../../Engine/Shaders/TexturedScene.pre", SunRenderingNodeShaderTypeSceneTextured)}
	};
	
	// GBuffer
	SunRenderingNode *gbuffer;
	gbuffer->setInputs(gbufferInputs);
	gbuffer->setOutputs(gbufferOutputs);
	gbuffer->setShaders(gbufferShaders);
	
	rootRenderNode = gbuffer;
}
