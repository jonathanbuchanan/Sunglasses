#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoordinates;

uniform mat4 model;
out vec2 outTextureCoordinates;

void main() {
    gl_Position = model * vec4(position, -0.5f, 1.0f);
    outTextureCoordinates = textureCoordinates;
}