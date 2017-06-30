#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <sunglasses/Graphics/Texture.h>

#include <tuple>
#include <utility>

namespace sunglasses {

namespace graphics {

/// A framebuffer attachment for color
class ColorAttachment {
public:
    /// Constructs the attachment with a size
    ColorAttachment(glm::ivec2 size) :
            texture(Image<unsigned char>(size), TextureMinification::Linear, TextureMagnification::Linear) {

    }

    operator Texture &() {
        return texture;
    }
private:
    /// The texture attatched to the framebuffer
    Texture texture;
};

/// A framebuffer attachment for depth
class DepthAttachment {
template<typename... T>
friend class Framebuffer;
public:
    /// Constructs the attachment with a size
    DepthAttachment(glm::ivec2 size) {
        glGenRenderbuffers(1, &rbo);

        glBindRenderbuffer(GL_RENDERBUFFER, rbo);

        // TODO: Add options for formatting
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    /// Attaches the attachment to a framebuffer
    /*void attach(size_t index) {
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }*/
private:
    /// The renderbuffer object
    GLuint rbo;
};

/// The interface for the Framebuffer class
class IFramebuffer {
public:
    /// Activates (binds) the framebuffer
    virtual void activate() = 0;

    /// Clears the framebuffer
    virtual void clear(glm::vec4 color) = 0;
    
    /// Returns the size of the framebuffer
    virtual glm::ivec2 getSize() = 0;

    /// Destroys the framebuffer
    virtual ~IFramebuffer() {

    }
private:

};

/*/// A special framebuffer for the window
class WindowFramebuffer : public IFramebuffer {
public:
    /// Constructs the framebuffer with a reference to the window
    WindowFramebuffer(const Window &_window) : window(_window) {

    }

    /// Activates (binds) the framebuffer
    virtual void activate() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    /// Clears the framebuffer
    virtual void clear(glm::vec4 color) {
        glClearColor(color.r, color.g, color.b, color.a);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /// Returns the size of the framebuffer
    virtual glm::ivec2 getSize() {
        return window.getSize();
    }
private:
    /// A reference to the window
    const Window &window;
};*/

/// An object containing buffers to be rendered to
template<typename... T>
class Framebuffer : public IFramebuffer {
public:
    /// Constructs the framebuffer
    Framebuffer(glm::ivec2 _size) :
            attachments(_size), size(_size) {
        glGenFramebuffers(1, &framebuffer);

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        // Attach the attachments
        attach(std::index_sequence_for<T...>{});

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            // ERROR!
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    /// Destroys the framebuffer
    virtual ~Framebuffer() {
        glDeleteFramebuffers(1, &framebuffer);
    }

    /// Binds the framebuffer for rendering
    virtual void activate() {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    }

    /// Clears the framebuffer with a color
    virtual void clear(glm::vec4 color = glm::vec4(1.0f)) {
        glClearColor(color.r, color.g, color.b, color.a);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    /// Returns the size of the framebuffer
    virtual glm::ivec2 getSize() {
        return size;
    }

    /// Returns the attachment at the given index
    template<int N>
    const typename std::tuple_element<N, std::tuple<T...>>::type & getAttachment() {
        return std::get<N>(attachments);
    }
private:
    /// Attaches all the attachments
    template<size_t... I>
    void attach(std::index_sequence<I...>) {
        auto a = {(attachElement(std::get<I>(attachments), I), 0)...};
    }

    /// Attaches an attachment
    template<typename A>
    void attachElement(A &element, size_t index);

    void attachElement(ColorAttachment &element, size_t index) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, ((Texture &)element).texture, 0);
    }

    void attachElement(DepthAttachment &element, size_t index) {

    }

    /// The OpenGL framebuffer object
    GLuint framebuffer;

    /// A tuple containing the attachments to the framebuffer
    std::tuple<T...> attachments;

    /// The size of the framebuffer
    glm::ivec2 size;
};

} // namespace
} // namespace

#endif
