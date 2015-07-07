#version 330 core
in vec2 outTextureCoordinates;
out vec4 color;

uniform sampler2D backgroundTexture;

void main() {
    vec3 result = vec3(texture(backgroundTexture, outTextureCoordinates));
    
    color = vec4(result, 1.0f);
}