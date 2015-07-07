#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec2 textureCoordinates;

out vec3 outFragmentPosition;
out vec2 outTextureCoordinates;
out vec4 outLightSpaceFragmentPosition;
out vec3 outNormal;

uniform mat4 model;
uniform mat3 normalMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightMatrix;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0f);
    
    outFragmentPosition = vec3(model * vec4(position, 1.0f));
    
    outTextureCoordinates = textureCoordinates;
    
    outLightSpaceFragmentPosition = lightMatrix * vec4(outFragmentPosition, 1.0f);
    
    outNormal = normalMatrix * normal;
}