#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace sunglasses {

class Shader;

/// A rectangle that is a component of every view
class Drawable {
public:
    /// Creates a copy of the object and returns a pointer (for polymorphism purposes)
    virtual Drawable * copy() const = 0;

    /// Passes uniforms (like color or a texture) to the shader
    virtual void uniforms(Shader &shader) = 0;
};

/// A drawable of a single color
class DrawableSolidColor : public Drawable {
public:
    /// Constructs the drawable with a color
    DrawableSolidColor(glm::vec4 _color);

    /// Creates a copy of the object and return a pointer
    virtual Drawable * copy() const;

    /// Passes the color as a uniform
    virtual void uniforms(Shader &shader);
    /// The color of the drawable
    glm::vec4 color;
};

/// A drawable of a single image
class DrawableImage : public Drawable {
public:

private:
    /// The OpenGL texture
    GLuint texture;
};

} // namespace

#endif
