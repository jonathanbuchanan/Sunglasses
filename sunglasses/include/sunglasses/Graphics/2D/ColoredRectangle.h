#ifndef COLOREDRECTANGLE_H
#define COLOREDRECTANGLE_H

#include <glm/glm.hpp>

namespace sunglasses {
namespace graphics {

/// A colored rectangle
struct ColoredRectangle {
	/// The underlying rendering data of the rectangle
	/**
	 * This is the data structure that contains the rendering data (color)
	 * for the rectangle. This can be passed in constructors without making
	 * references to a position and a size.
	 */
	struct Color {
		Color(const glm::vec4 &_color = glm::vec4(1.0f)) : color(_color) { }
		operator glm::vec4() const { return color; }
		glm::vec4 color;
	} color;
	
    /// Constructs the rectangle with a color
    ColoredRectangle(Color _color, const glm::ivec2 &position, const glm::ivec2 &size);

    /// The position of the rectangle
    const glm::ivec2 &position;
    
    /// The size of the rectangle
    const glm::ivec2 &size;
};

}
}

#endif
