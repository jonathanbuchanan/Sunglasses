// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H

#include "../Core/Base.h"
#include "../Core/Service.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

namespace sunglasses {

class CursorManager : public Service {
public:

    CursorManager();
    CursorManager(GLFWwindow *_window);
    CursorManager(GLFWwindow *_window, bool disable);

    void initialize(GLFWwindow *_window);
    void initialize(GLFWwindow *_window, bool disable);

    void update();

    void enableCursor();
    void disableCursor();
    int getMode();

    glm::vec2 getCursorPosition();
    glm::vec2 getCursorPositionNDC();

    void subscribe(Base *subscriber);

    GLFWwindow *window;
private:
    std::vector<Base *> subscribers;
};

} // namespace

#endif
