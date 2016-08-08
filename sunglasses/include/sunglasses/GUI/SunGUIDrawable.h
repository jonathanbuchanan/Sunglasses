#ifndef SUNGUIDRAWABLE_H
#define SUNGUIDRAWABLE_H

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace sunglasses {

class SunShader;

/// A rectangle that is a component of every view
class SunGUIDrawable {
public:
    /// Creates a copy of the object and returns a pointer (for polymorphism purposes)
    virtual SunGUIDrawable * copy() const = 0;

    /// Passes uniforms (like color or a texture) to the shader
    virtual void uniforms(SunShader &shader) = 0;
};

/// A drawable of a single color
class SunGUIDrawableSolidColor : public SunGUIDrawable {
public:
    /// Constructs the drawable with a color
    SunGUIDrawableSolidColor(glm::vec4 _color);

    /// Creates a copy of the object and return a pointer
    virtual SunGUIDrawable * copy() const;

    /// Passes the color as a uniform
    virtual void uniforms(SunShader &shader);
    /// The color of the drawable
    glm::vec4 color;
};

/// A drawable of a single image
class SunGUIDrawableImage : public SunGUIDrawable {
public:

private:
    /// The OpenGL texture
    GLuint texture;
};

} // namespace

#endif
