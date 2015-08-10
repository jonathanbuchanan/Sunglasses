#ifndef OpenGL_Test_3_SunGame_h
#define OpenGL_Test_3_SunGame_h

#include <iostream>
#include <unistd.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class SunScene;

class SunGame {
public:
    SunGame() {
        
    }
    
    void loop();
    void initialize(bool _useMSAA, GLint _MSAASampleCount);
    
    inline SunScene * getScene() { return scene; }
    inline void setScene(SunScene *_scene) { scene = _scene; }
    
    inline GLFWwindow * getWindow() { return window; }
    inline void setWindow(GLFWwindow *_window) { window = _window; }
    
    inline GLfloat & getScreenWidth() { return screenWidth; }
    inline GLfloat & getScreenHeight() { return screenHeight; }
private:
    SunScene *scene;
    GLFWwindow *window;
    GLfloat screenWidth = 800;
    GLfloat screenHeight = 600;
};

#endif
