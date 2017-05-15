#include <sunglasses/Graphics/2D/TexturedRectangle.h>

namespace sunglasses {
namespace graphics {

TexturedRectangle::TexturedRectangle(Texture &_texture, glm::ivec2 _textureSize,
    const glm::ivec2 &_position, const glm::ivec2 &_size) :
        texture(_texture), textureSize(_textureSize), position(_position), size(_size) {

}

}
}
