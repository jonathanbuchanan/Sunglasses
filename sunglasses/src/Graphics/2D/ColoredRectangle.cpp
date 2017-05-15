#include <sunglasses/Graphics/2D/ColoredRectangle.h> 

namespace sunglasses {
namespace graphics {

ColoredRectangle::ColoredRectangle(glm::vec4 _color, const glm::ivec2 &_position, const glm::ivec2 &_size)
        : color(_color), position(_position), size(_size) {

}

}
}
