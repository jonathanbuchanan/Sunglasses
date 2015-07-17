#version 330 core
layout (location = 0) out vec3 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec4 color;

in vec3 outFragmentPosition;
in vec2 outTextureCoordinates;
in vec4 outLightSpaceFragmentPosition;
in vec3 outNormal;

struct Material {
    vec3 color;
    float shininess;
};

uniform Material material;

void main() {
    position = outFragmentPosition;
    normal = outNormal;
    color.rgb = material.color;
    color.a = 1;
}