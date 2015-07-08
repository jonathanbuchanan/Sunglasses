#version 330 core
in vec2 outTextureCoordinates;
out vec4 color;

uniform sampler2D backgroundTexture;
uniform float exposure;
uniform bool doHDR;

void main() {
    vec3 nonclamped = vec3(texture(backgroundTexture, outTextureCoordinates));
    
    vec3 result = vec3(1.0f) - exp(-nonclamped * exposure);
    
    color = vec4(result, 1.0f);
}