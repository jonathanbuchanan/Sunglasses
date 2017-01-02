#ifndef FRAMEBUFFERQUEUE_H
#define FRAMEBUFFERQUEUE_H

#include <stack>
#include <functional>

#include <sunglasses/Graphics/Framebuffer.h>

namespace sunglasses {

namespace graphics {

/// A class that maintains a queue of framebuffers
/**
 * This is used in order to maintain order in drawing to framebuffers.
 * After any drawing operation to a framebuffer is completed, the previous framebuffer
 * is subsequently bound.
 */
class FramebufferQueue {
public:
    /// Adds a framebuffer into the queue and binds it
    void push(IFramebuffer &framebuffer);

    /// Removes the top framebuffer from the queue and binds the next
    void pop();

    /// Returns a reference to the framebuffer at the top of the stack
    IFramebuffer & top();
private:
    /// The stack of framebuffers
    std::stack<std::reference_wrapper<IFramebuffer>> stack;
};

} // namespace
} // namespace

#endif
