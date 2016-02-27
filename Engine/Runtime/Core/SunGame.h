// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef OpenGL_Test_3_SunGame_h
#define OpenGL_Test_3_SunGame_h

#include <iostream>
#include <unistd.h>
#include <string>
#include <map>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "SunBase.h"

#include "SunScene.h"
#include "../Graphics/SunWindowManager.h"
#include "../Input/SunKeyboardManager.h"
#include "../Input/SunCursorManager.h"
#include "../Input/SunMouseButtonManager.h"
#include "../Output/SunLogger.h"

using namespace std;

class SunScene;

class SunGame : public SunBase {
public:
    SunGame() { }

	void run();
	virtual void loop();
    void updateServices();
    void cleanUp();
    void initialize();
	void initialize(std::string title, glm::vec4 color);
protected:
	SunScene *scene;
    GLFWwindow *window;
};

#endif
