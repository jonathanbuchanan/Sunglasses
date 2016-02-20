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

#include "Core/SunBase.h"

#include "Input/SunKeyboardManager.h"
#include "Input/SunCursorManager.h"
#include "Input/SunMouseButtonManager.h"
#include "Output/SunLogger.h"

using namespace std;

extern GLfloat screenWidth;
extern GLfloat screenHeight;

class SunScene;

class SunGame : public SunBase {
public:
    SunGame() { }
    
    void loop();
    void updateServices();
    void cleanUp();
    void initialize();

    inline std::string & getWindowTitle() { return windowTitle; }
    inline void setWindowTitle(std::string w) { windowTitle = w; }
    
    inline glm::vec4 & getClearColor() { return clearColor; }
    inline void setClearColor(glm::vec4 c) { clearColor = c; }
    
    inline GLfloat & getScreenWidth() { return screenWidth; }
    inline GLfloat & getScreenHeight() { return screenHeight; }
protected:
    GLFWwindow *window;
   
    std::string windowTitle;
    glm::vec4 clearColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
    
private:
};

#endif
