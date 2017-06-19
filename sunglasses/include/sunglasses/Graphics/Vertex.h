#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <utility>
#include <initializer_list>

namespace sunglasses {

namespace WIP {

/// A vertex data type for use in the 2D plane
struct Vertex2D {
public:
	/// The position of the vertex
	glm::vec2 position;
	
	/// The texture coordinates of the vertex
	glm::vec2 textureCoordinates;
	
	/// Enables its vertex attributes
	static void attributes() {
		int stride = sizeof(Vertex2D);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offsetof(Vertex2D, position));
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offsetof(Vertex2D, textureCoordinates));
		glEnableVertexAttribArray(1);
	}
};

}
} // namespace

#endif
