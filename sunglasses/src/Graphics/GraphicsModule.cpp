#include <sunglasses/Graphics/GraphicsModule.h>

namespace sunglasses {
namespace graphics {

GraphicsModule::GraphicsModule(glm::ivec2 windowSize, std::string windowTitle, std::initializer_list<std::reference_wrapper<IPass>> _passes) :
        window(windowSize, windowTitle), passes(_passes) {
            
}

void GraphicsModule::update() {
    window.update();
}

void GraphicsModule::run() {
    for (IPass &pass : passes) {
        pass.render();
    }
    window.swapBuffers();

}

void GraphicsModule::addPass(IPass &pass) {
    passes.push_back(std::ref(pass));
}

}
}
