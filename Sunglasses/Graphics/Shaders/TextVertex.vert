#version 330 core
layout (location = 0) in vec4 vertex;
out vec2 textureCoordinates;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(vertex.xy, 0.0f, 1.0f);
    gl_Position.z = -1.0;
    textureCoordinates = vertex.zw;
}