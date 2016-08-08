// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNMOUSEMANAGER_H
#define SUNMOUSEMANAGER_H

#include "../Core/SunBase.h"
#include "../Core/SunService.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

namespace sunglasses {

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
    glm::vec2 getCursorPositionNDC();

    void subscribe(SunBase *subscriber);

    GLFWwindow *window;
private:
    std::vector<SunBase *> subscribers;
};

} // namespace

#endif
