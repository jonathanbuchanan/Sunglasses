#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textureCoordinates;

out vec2 outTextureCoordinates;

uniform mat4 model;

void main() {
    gl_Position = model * vec4(position, 0.0f, 1.0f);
    outTextureCoordinates = textureCoordinates;
}