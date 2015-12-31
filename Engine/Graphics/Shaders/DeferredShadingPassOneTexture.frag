#version 330 core
layout (location = 0) out vec4 position;
layout (location = 1) out vec4 normal;
layout (location = 2) out vec4 color;

struct Material {
    sampler2D diffuse;
    float shininess;
};

in vec3 outFragmentPosition;
in vec2 outTextureCoordinates;
in vec4 outLightSpaceFragmentPosition;
in vec3 outNormal;

uniform Material material;

void main() {
    position = vec4(outFragmentPosition, 1.0f);
    normal = vec4(normalize(outNormal), 1.0f);
    color = vec4(vec3(texture(material.diffuse, outTextureCoordinates)), 1.0f);
}