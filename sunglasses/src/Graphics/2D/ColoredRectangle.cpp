#include <sunglasses/Graphics/2D/ColoredRectangle.h> 

namespace sunglasses {
namespace graphics {

ColoredRectangle::ColoredRectangle(Color _color, const glm::ivec2 &_position, const glm::ivec2 &_size)
        : color(_color), position(_position), size(_size) {

}

}
}
