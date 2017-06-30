#ifndef GRAPHICSMODULE_H
#define GRAPHICSMODULE_H

#include <sunglasses/Core/Program.h>

#include <sunglasses/Graphics/Window.h>
#include <sunglasses/Graphics/RenderingPipeline.h>

#include <list>
#include <functional>

namespace sunglasses {
namespace graphics {
    
class IPass;

/// The module that controls graphics
class GraphicsModule : public Module {
public:
    /// Constructs the module with dimensions and a title
    GraphicsModule(glm::ivec2 windowSize, std::string windowTitle,
    	RenderingPipeline *_pipeline = nullptr);

    /// Updates the module
    virtual void update();

    /// Runs the module (renders)
    virtual void run();

    /// The window
    Window window;

    /// The rendering pipeline
   	RenderingPipeline *pipeline;
};

}
}

#endif
