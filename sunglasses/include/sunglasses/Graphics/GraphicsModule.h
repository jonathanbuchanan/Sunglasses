#ifndef GRAPHICSMODULE_H
#define GRAPHICSMODULE_H

#include <sunglasses/Core/Program.h>

#include <sunglasses/Graphics/Window.h>

#include <list>
#include <functional>

namespace sunglasses {
namespace graphics {
    
class IPass;

/// The module that controls graphics
class GraphicsModule : public Module {
public:
    /// Constructs the module with dimensions and a title
    GraphicsModule(glm::ivec2 windowSize, std::string windowTitle, std::initializer_list<std::reference_wrapper<IPass>> _passes);

    /// Updates the module
    virtual void update();

    /// Runs the module (renders)
    virtual void run();
    
    /// Adds a pass to the list of passes
    void addPass(IPass &pass);

    /// The window
    Window window;
private:
    /// The list of passes to render
    std::list<std::reference_wrapper<IPass>> passes;
};

/// The interface for Pass
class IPass {
public:
    /// Renders the pass
    virtual void render() = 0;
private:
    
};

/// Represents a 'pass' in the rendering process
template<typename F, typename R>
class Pass : public IPass {
public:
    /// Constructs the pass with a framebuffer and a clear color
    Pass(F &_framebuffer, glm::vec4 _clearColor)
            : framebuffer(_framebuffer), clearColor(_clearColor) {

    }

    /// Renders the pass
    virtual void render() {
        // 1. size viewport
        glm::ivec2 size = framebuffer.getSize();
        glViewport(0, 0, size.x, size.y);

        // 2. bind framebuffer
        framebuffer.activate();

        // 3. clear
        framebuffer.clear(clearColor);

        // 4. draw
        renderer.draw();
    }
private:
    /// The framebuffer used in the pass
    F &framebuffer;
    
    /// The renderer used in the pass
    R &renderer;

    /// The clear color
    glm::vec4 clearColor;
};

}
}

#endif
