#include <sunglasses/Graphics/GraphicsModule.h>

namespace sunglasses {
namespace graphics {

GraphicsModule::GraphicsModule(glm::ivec2 windowSize, std::string windowTitle, RenderingPipeline *_pipeline) :
        window(windowSize, windowTitle), pipeline(_pipeline) {
            
}

void GraphicsModule::update() {
    window.update();
}

void GraphicsModule::run() {
	if (pipeline != nullptr)
    	pipeline->render();
}

}
}
