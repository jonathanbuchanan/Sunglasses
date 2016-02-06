#ifndef SUNMOUSEMANAGER_H
#define SUNMOUSEMANAGER_H

#include "SunNode.h"
#include "SunService.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class SunCursorManager : public SunService {
public:
    
    SunCursorManager();
    SunCursorManager(GLFWwindow *_window);
    SunCursorManager(GLFWwindow *_window, bool disable);
    
    void initialize(GLFWwindow *_window);
    void initialize(GLFWwindow *_window, bool disable);
    
    void update();
    
    void enableCursor();
    void disableCursor();
    int getMode();
    
    glm::vec2 getCursorPosition();
    
    void subscribe(SunNode *subscriber);
    
    GLFWwindow *window;
private:
    std::vector<SunNode *> subscribers;
};

#endif