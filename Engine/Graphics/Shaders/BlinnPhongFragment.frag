// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core

struct Material {
    vec3 color;
    sampler2D diffuse;
    sampler2D normal;
    float shininess;
};

in vec3 outFragmentPosition;
in vec4 outLightSpaceFragmentPosition;
in vec3 outTangentLightPosition;
in vec3 outTangentViewPosition;
in vec3 outTangentFragmentPosition;
in vec2 outTextureCoordinates;

uniform vec3 viewPosition;

uniform Material material;

uniform sampler2D shadowMap;
uniform float farPlane;

struct DirectionalLight {
    // Diffuse and specular
    vec3 diffuseColor;
    vec3 specularColor;
    
    // Direction
    vec3 direction;
};

struct PointLight {
    // Diffuse and specular
    vec3 diffuseColor;
    vec3 specularColor;
    
    // Position
    vec3 position;
    
    // Attenuation
    float constant;
    float linear;
    float quadratic;
};

struct Spotlight {
    // Diffuse, specular, and cutoff
    vec3 diffuseColor;
    vec3 specularColor;
    float cutoff;
    
    // Position and Direction
    vec3 position;
    vec3 direction;
    
    // Attenuation
    float constant;
    float linear;
    float quadratic;
};

uniform DirectionalLight directionalLight;
uniform PointLight pointLight;

out vec4 outColor;

float calculateShadow(PointLight _pointLight) {
    vec3 fragmentToLight = outFragmentPosition - _pointLight.position;
    float closestDepth = texture(shadowMap, fragmentToLight.xy).r;
    closestDepth *= farPlane;
    float currentDepth = length(fragmentToLight);
    float bias = 0.05;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    
    return shadow;
}

float calculateShadowForDirectionalLight(DirectionalLight _directionalLight) {
    vec3 projCoords = outLightSpaceFragmentPosition.xyz / outLightSpaceFragmentPosition.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;
    
    return shadow;
}

/*vec3 calculateDirectionalLight(DirectionalLight _directionalLight) {
    vec3 normalizedNormal = normalize(outNormal);
    vec3 lightDirection = normalize(-_directionalLight.direction);
    float difference = max(dot(normalizedNormal, lightDirection), 0);
    vec3 diffuseColor = material.color * _directionalLight.diffuseColor * difference;
    
    float specularConstant = 0.5;
    vec3 viewDirection = normalize(viewPosition - outFragmentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, outNormal);
    float specular = pow(max(dot(viewDirection, reflectionDirection), 0), 32);
    vec3 specularColor = material.color * _directionalLight.specularColor * specular * specularConstant;
    
    return diffuseColor + specularColor;
}

vec3 calculatePointLight(PointLight _pointLight) {
    vec3 normalizedNormal = normalize(outNormal);
    vec3 lightDirection = normalize(_pointLight.position - outFragmentPosition);
    float difference = max(dot(normalizedNormal, lightDirection), 0);
    vec3 diffuseColor = material.color * _pointLight.diffuseColor * difference;
    
    float specularConstant = 0.5;
    vec3 viewDirection = normalize(viewPosition - outFragmentPosition);
    vec3 halfwayDirection = normalize(lightDirection + viewDirection);
    float specular = pow(max(dot(viewDirection, halfwayDirection), 0), 512);
    vec3 specularColor = material.color * _pointLight.specularColor * specular * specularConstant;
    
    float distance = length(_pointLight.position - outFragmentPosition);
    float attenuation = 1.0f / (_pointLight.constant + _pointLight.linear * distance + _pointLight.quadratic * (distance * distance));
    
    return (diffuseColor + specularColor) * attenuation;
}*/

void main() {
    vec3 normal = texture(material.normal, outTextureCoordinates).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    
    vec3 color = texture(material.diffuse, outTextureCoordinates).rgb;
    
    vec3 ambient = 0.1 * color;
    
    vec3 lightDir = normalize(outTangentLightPosition - outTangentFragmentPosition);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    
    vec3 viewDir = normalize(outTangentViewPosition - outTangentFragmentPosition);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec * color;
    
    vec3 result = ambient + (calculateShadowForDirectionalLight(directionalLight) * (diffuse + specular));
    
    outColor = vec4(vec3(texture(material.diffuse, outTextureCoordinates)), 1.0);
}