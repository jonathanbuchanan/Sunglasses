// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Core/Scene.h>

#include <sunglasses/Graphics/Renderer.h>

namespace sunglasses {

Scene::Scene() {

}

void Scene::init() {

}

void Scene::cycle() {
    Action update("update");
    update.setRecursive(true);
    sendAction(update, root.get());
    renderer->render();
    renderer->swapBuffers();
}

} // namespace
