// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/Renderer.h>
#include <sunglasses/Core/Scene.h>

namespace sunglasses {

namespace graphics {

void Renderer::render() {
    Action renderAction("render");
    renderAction.setRecursive(true);

    sendAction(renderAction, root);
}

void Renderer::swapBuffers() {
    // Swap the buffers
    services.get<WindowManager>()->swapBuffers();
}

void Renderer::init() {
    root = new Node();
}

} // namespace

} // namespace
