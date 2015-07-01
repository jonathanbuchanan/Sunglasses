#version 330 core
layout (location = 0) in vec4 vertex;
out vec2 textureCoordinates;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(vertex.xy, 1.0f, 1.0f);
    textureCoordinates = vertex.zw;
}