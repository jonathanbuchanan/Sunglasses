#ifndef SUNKEYBOARDMANAGER_H
#define SUNKEYBOARDMANAGER_H

#include "SunNode.h"
#include <GLFW/glfw3.h>
#include <vector>

class SunKeyboardManager {
public:
    void initialize(GLFWwindow *_window);
    void update();
    
    void subscribe(SunNode *subscriber, int key);
    
    GLFWwindow *window;
private:
    std::vector<std::pair<SunNode *, int>> subscribers;
    std::vector<int> pressed;
};

#endif
