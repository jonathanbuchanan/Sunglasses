// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNMOUSEBUTTONMANAGER_H
#define SUNMOUSEBUTTONMANAGER_H

#include "SunNode.h"
#include "SunService.h"
#include <GLFW/glfw3.h>

class SunMouseButtonManager : public SunService {
public:
    
    SunMouseButtonManager();
    SunMouseButtonManager(GLFWwindow *_window);
    
    void initialize(GLFWwindow *_window);
    void update();
    
    void subscribe(SunNode *subscriber, int button, SunButtonEvent event);
    
    SunButtonState pollButton(int button);
    
    GLFWwindow *window;
private:
    std::vector<std::tuple<SunNode *, int, SunButtonEvent>> subscribers;
    std::array<int, 8> buttons;
};

#endif