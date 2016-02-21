// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNWINDOWMANAGER_H
#define SUNWINDOWMANAGER_H

#include "Core/SunBase.h"
#include "Core/SunService.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class SunWindowManager : public SunService {
public:
	SunWindowManager();
	SunWindowManager(glm::vec2 _size, std::string _title, glm::vec4 _clearColor);
	
	void initialize();
	void terminate();

	void swapBuffers();
	void setWindowShouldClose();

	void calculateDelta();

	inline GLFWwindow * getWindow() { return window; }

	inline glm::vec2 getSize() { return size; }
	inline void setSize(glm::vec2 s) { size = s; }

	inline std::string getTitle() { return title; }
	inline void setTitle(std::string t) { title = t; }

	inline void setClearColor(glm::vec4 c) { clearColor = c; }

	inline double getDelta() { return delta; }
private:
	GLFWwindow *window;

	glm::vec2 size;
	std::string title;

	glm::vec4 clearColor;

	double lastFrame;
	double delta;
};

#endif
