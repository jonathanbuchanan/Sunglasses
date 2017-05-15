#ifndef TEXTUREDRECTANGLE_H
#define TEXTUREDRECTANGLE_H

#include <glm/glm.hpp>
#include <sunglasses/Graphics/Texture.h>

namespace sunglasses {
namespace graphics {

/// A textured rectangle
struct TexturedRectangle {
    /// Constructs the rectangle with a texture reference and size
    TexturedRectangle(Texture &_texture, glm::ivec2 _textureSize,
            const glm::ivec2 &_position, const glm::ivec2 &_size);
    
    /// A reference to the texture
    Texture &texture;
    
    /// The size of the texture in pixels
    /**
     * If this value is set to glm::ivec2(0, 0), that means
     * the texture be stretched to fit the size of what it
     * is drawn on.
     */
    glm::ivec2 textureSize;
    
    /// The position of the rectangle
    const glm::ivec2 &position;
    
    /// The size of the rectangle
    const glm::ivec2 &size;
};

}
}

#endif
