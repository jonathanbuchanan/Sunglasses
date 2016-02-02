#ifndef SUNKEYBOARDMANAGER_H
#define SUNKEYBOARDMANAGER_H

#include "SunNode.h"
#include "SunService.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <array>

enum SunButtonState {
    SunButtonStateUp = 0,
    SunButtonStateDown = 1
};

enum SunButtonEvent {
    SunButtonEventUpSingle = 0,
    SunButtonEventDownSingle = 1,
    
    SunButtonEventUpContinuous = 2,
    SunButtonEventDownContinuous = 3
};

class SunKeyboardManager : public SunService {
public:
    
    SunKeyboardManager();
    
    void initialize(GLFWwindow *_window);
    void update();
    
    void subscribe(SunNode *subscriber, int key, SunButtonEvent event);
    
    SunButtonState pollKey(int key);
    
    GLFWwindow *window;
private:
    std::vector<std::tuple<SunNode *, int, SunButtonEvent>> subscribers;
    std::array<int, 512> keys;
};

#endif
