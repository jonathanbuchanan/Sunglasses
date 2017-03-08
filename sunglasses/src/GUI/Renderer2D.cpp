// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Renderer2D.h>

#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/string_cast.hpp>

namespace sunglasses {
namespace GUI {

const std::string fill_vertex = R"(
#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;

void main() {
    gl_Position = projection * model * vec4(vertex, 0.0f, 1.0f);
}
)";

GLuint __indices[] = {
    0, 1, 2,
    1, 2, 3
};

const std::string fill_fragment = R"(
#version 330 core

out vec4 color;

uniform vec4 fillColor;

void main() {
    color = fillColor;
}
)";

const std::string texture_vertex = R"(
#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat3 textureScale;

out VertexOut {
    vec2 texCoords;
} vertexOut;

void main() {
    gl_Position = projection * model * vec4(vertex, 0.0f, 1.0f);
    vertexOut.texCoords = (textureScale * vec3(texCoords, 1.0f)).xy;
}
)";

const std::string texture_fragment = R"(
#version 330 core

out vec4 color;

in VertexOut {
    vec2 texCoords;
} fragmentIn;

uniform sampler2D sampler;

void main() {
    color = texture(sampler, fragmentIn.texCoords);
}
)";

const std::string text_vertex = R"(
#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;

out VertexOut {
    vec2 texCoords;
} vertexOut;

void main() {
    gl_Position = projection * model * vec4(vertex, 0.0f, 1.0f);
    vertexOut.texCoords = texCoords;
}
)";

const std::string text_fragment = R"(
#version 330 core

out vec4 color;

in VertexOut {
    vec2 texCoords;
} fragmentIn;

uniform sampler2D sampler;
uniform vec4 textColor;

void main() {
    color = textColor * vec4(1.0f, 1.0f, 1.0f, texture(sampler, fragmentIn.texCoords).r);
}
)";

Renderer2D::Renderer2D(sunglasses::graphics::Window &_window) :
    window(_window), fillShader(fill_vertex, fill_fragment),
    textureShader(texture_vertex, texture_fragment, {"sampler"}),
    textShader(text_vertex, text_fragment, {"sampler"}) {

}

void Renderer2D::draw(glm::ivec2 origin, glm::ivec2 size, glm::vec4 color) {
    fillShader.use();

    // Pass the projection matrix
    glm::ivec2 windowSize = window.getSize();
    glm::mat4 projection = glm::ortho(0.0f, (float)windowSize.x, (float)windowSize.y, 0.0f);
    fillShader["projection"] = projection;

    // Generate a model matrix
    glm::mat4 model;

    model = glm::translate(model, glm::vec3(origin, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    fillShader["model"] = model;

    // Pass the uniforms of the drawable
    fillShader["fillColor"] = color;

    // Draw the rectangle
    rectangle.draw();
}

void Renderer2D::draw(glm::ivec2 origin, glm::ivec2 size, glm::ivec2 textureSize, const graphics::Texture &texture) {
    textureShader.use();

    // Pass the projection matrix
    glm::ivec2 windowSize = window.getSize();
    glm::mat4 projection = glm::ortho(0.0f, (float)windowSize.x, (float)windowSize.y, 0.0f);
    textureShader["projection"] = projection;

    // Generate a model matrix
    glm::mat4 model;

    model = glm::translate(model, glm::vec3(origin, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    textureShader["model"] = model;

    // Create a texture scale matrix
    glm::mat3 textureScale;

    glm::vec2 scale;
    if (textureSize != glm::ivec2(0))
        scale = glm::vec2(size / textureSize);
    else
        scale = glm::vec2(1.0f);

    textureScale = glm::scale(textureScale, scale);

    textureShader["textureScale"] = textureScale;

    // Pass the uniforms of the drawable
    textureShader.textures["sampler"] = texture;

    // Draw the rectangle
    rectangle.draw();
}

void Renderer2D::draw(glm::ivec2 origin, std::string text, glm::vec4 color, Font &font) {
    textShader.use();

    // Pass the projection matrix
    glm::ivec2 size = window.getSize();
    glm::mat4 projection = glm::ortho(0.0f, (float)size.x, (float)size.y, 0.0f);
    textShader["projection"] = projection;

    // Set the text color
    textShader["textColor"] = color;

    glm::ivec2 pen = origin;

    // Iterate through the characters of the string
    for (char &character : text) {
        // Load the glyph corresponding to the character
        Glyph &glyph = font.glyphs[character];

        // Generate a model matrix
        glm::mat4 model;

        model = glm::translate(model, glm::vec3(pen.x + glyph.bearing.x, pen.y - glyph.bearing.y, 0.0f));
        model = glm::scale(model, glm::vec3(glyph.size, 1.0f));

        textShader["model"] = model;

        textShader.textures["sampler"] = glyph.texture;

        // Draw the rectangle
        rectangle.draw();

        // Increase the pen position
        pen += (glyph.advance >> 6);
    }
}

} // namespace
} // namespace
