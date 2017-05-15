#ifndef COLOREDRECTANGLE_H
#define COLOREDRECTANGLE_H

#include <glm/glm.hpp>

namespace sunglasses {
namespace graphics {

/// A colored rectangle
struct ColoredRectangle {
    /// Constructs the rectangle with a color
    ColoredRectangle(glm::vec4 _color, const glm::ivec2 &position, const glm::ivec2 &size);
    
    /// The color of the rectangle
    glm::vec4 color;

    /// The position of the rectangle
    const glm::ivec2 &position;
    
    /// The size of the rectangle
    const glm::ivec2 &size;
};

}
}

#endif
