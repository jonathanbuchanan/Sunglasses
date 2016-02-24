// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunDirectionalShadowMapRenderingNode.h"

SunShader SunDirectionalShadowMapRenderingNode::shader = {};
bool SunDirectionalShadowMapRenderingNode::shaderInitialized = false;

SunDirectionalShadowMapRenderingNode::SunDirectionalShadowMapRenderingNode() {
	output = new SunRenderingNodeOutput();
}

SunDirectionalShadowMapRenderingNode::SunDirectionalShadowMapRenderingNode(glm::vec2 _size) {
	output = new SunRenderingNodeOutput();
	size = _size;
}

SunDirectionalShadowMapRenderingNode::SunDirectionalShadowMapRenderingNode(glm::vec2 _size, SunDirectionalLight *_light) {
	output = new SunRenderingNodeOutput();
	size = _size;
	light = _light;
}

SunDirectionalShadowMapRenderingNode::SunDirectionalShadowMapRenderingNode(SunNode *_root) {
	output = new SunRenderingNodeOutput();
	root = _root;
}

void SunDirectionalShadowMapRenderingNode::init() {
	if (shaderInitialized == false) {
		shaderInitialized = true;
		shader = SunShader("../../Engine/Shaders/Old/ShadowMapVertex.vert", "../../Engine/Shaders/Old/ShadowMapFragment.frag");
	}
	addAction("render", &SunDirectionalShadowMapRenderingNode::render);

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &output->texture);
	glBindTexture(GL_TEXTURE_2D, output->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, resolution.x, resolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, output->texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SunDirectionalShadowMapRenderingNode::render(SunAction action) {
	GLdouble delta = ((SunWindowManager *)getService("window_manager"))->getDelta();

	// Create the light-space matrix
	glm::mat4 projection = glm::ortho(-size.x, size.x, -size.y, size.y, nearPlane, farPlane);
	glm::mat4 view = glm::lookAt(-light->getDirection(), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); 
	glm::mat4 lightMatrix = projection * view;
	
	glViewport(0, 0, resolution.x, resolution.y);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClear(GL_DEPTH_BUFFER_BIT);
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "lightMatrix"), 1, GL_FALSE, glm::value_ptr(lightMatrix));
	shader.send("", delta, root);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
} 
