#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <sunglasses/Graphics/Texture.h>

#include <tuple>
#include <utility>

namespace sunglasses {

/// A framebuffer attachment for color
class ColorAttachment {
public:
    /// Constructs the attachment with a size
    ColorAttachment(glm::ivec2 size) {
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    /// Attaches the attachment to a framebuffer
    void attach(size_t index) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, texture, 0);
    }
private:
    /// The texture attatched to the framebuffer
    GLuint texture;
};

/// A framebuffer attachment for depth
class DepthAttachment {
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
    void attach(size_t index) {
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
private:
    /// The renderbuffer object
    GLuint rbo;
};

/// An object containing buffers to be rendered to
template<typename... T>
class Framebuffer {
public:
    /// Constructs the framebuffer
    Framebuffer(glm::ivec2 _size) :
            attachments(_size) {
        glGenFramebuffers(1, &framebuffer);

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            // ERROR!
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Attach the attachments
        attach(std::index_sequence_for<T...>{});
    }

    /// Prepares the framebuffer for rendering
    void prepareForRendering() {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
    }

    /// Returns the attachment at the given index
    template<int N>
    const typename std::tuple_element<N, std::tuple<T...>>::type & getAttachment() {
        return std::get<N>(attachments);
    }

    /// Destroys the framebuffer
    ~Framebuffer() {
        glDeleteFramebuffers(1, &framebuffer);
    }
private:
    /// Attaches all the attachments
    template<size_t... I>
    void attach(std::index_sequence<I...>) {
        auto a = {(attachElement(std::get<I>(attachments)), 0)...};
    }

    /// Attaches an attachment
    template<typename A>
    void attachElement(A &element) {
        element.attach(0);
    }

    /// The OpenGL framebuffer object
    GLuint framebuffer;

    /// A tuple containing the attachments to the framebuffer
    std::tuple<T...> attachments;

    /// The size of the framebuffer
    glm::ivec2 size;
};

} // namespace

#endif
