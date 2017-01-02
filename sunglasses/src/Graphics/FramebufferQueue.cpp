#include <sunglasses/Graphics/FramebufferQueue.h>

namespace sunglasses {

void FramebufferQueue::push(IFramebuffer &framebuffer) {
    stack.push(framebuffer);

    ((IFramebuffer &)stack.top()).activate();
}

void FramebufferQueue::pop() {
    stack.pop();

    ((IFramebuffer &)stack.top()).activate();
}

IFramebuffer & FramebufferQueue::top() {
    return stack.top();
}

}
