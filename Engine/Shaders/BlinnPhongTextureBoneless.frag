// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core
layout (location = 0) out vec4 fragmentColor;
layout (location = 1) out vec4 bloomColor;

struct Material {
    sampler2D diffuse;
    float shininess;
};

in vec3 outFragmentPosition;
in vec2 outTextureCoordinates;
in vec4 outLightSpaceFragmentPosition;
in vec3 outNormal;

uniform vec3 viewPosition;

uniform sampler2D shadowMap;

uniform Material material;

uniform float farPlane;

struct DirectionalLight {
    // Color
    vec3 color;
    
    // Direction
    vec3 direction;
};

struct PointLight {
    // Color
    vec3 color;
    
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

vec3 calculateLighting(PointLight _pointLight) {
    // Diffuse Lighting
    
    
    // Normalize the normal
    vec3 _normal = normalize(outNormal);
    
    // Calculate the direction of the light to the fragment
    vec3 lightDirection = normalize(_pointLight.position - outFragmentPosition);
    
    // Calculate the dot product of the normal and the light direction, then choose 0 if lower than 0
    float diffuse = max(dot(_normal, lightDirection), 0.0);
    
    
    // Specular Lighting
    
    
    // Calculate the direction of the view to the fragment
    vec3 viewDirection = normalize(viewPosition - outFragmentPosition);
    
    // Calculate the halfway vector
    vec3 halfway = normalize(lightDirection + viewDirection);
    
    // Calculate the dot product of the normal and the halfway vector, then choose 0 if lower than 0, then raise to the shininess exponent
    float specular = pow(max(dot(_normal, halfway), 0.0), material.shininess);
    
    // Return the diffuse value + the specular value
    return _pointLight.color * (diffuse + specular);
}

vec3 calculateLighting(DirectionalLight _directionalLight) {
    // Diffuse Lighting
    
    // Normalize the normal
    vec3 _normal = normalize(outNormal);
    
    // Normalize the light direction
    vec3 lightDirection = normalize(_directionalLight.direction);
    
    // Calculate the dot product of the normal and the light direction, then choose 0 if lower than 0
    float diffuse = max(dot(_normal, lightDirection), 0.0);
    
    
    // Specular Lighting
    
    
    // Calculate the direction of the view to the fragment
    vec3 viewDirection = normalize(viewPosition - outFragmentPosition);
    
    // Calculate the halfway vector
    vec3 halfway = normalize(lightDirection + viewPosition);
    
    // Calculate the dot product of the normal and the halfway vector, then choose 0 if lower than 0, then raise to the shininess exponent
    float specular = pow(max(dot(_normal, halfway), 0.0), material.shininess);
    
    // Return the diffuse value + the specular value
    return _directionalLight.color * (diffuse + specular);
}

void main() {
    vec3 color = vec3(texture(material.diffuse, outTextureCoordinates));
    
    vec3 ambient = 0.1f * color;
    
    vec3 pointLightColor = calculateLighting(pointLight);
    
    vec3 result = ambient + (color * pointLightColor);
    
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    
    bloomColor = vec4(0.0, 0.0, 0.0, 1.0);
    if (brightness > 1.0)
        bloomColor = vec4(result, 1.0);
    
    fragmentColor = vec4(result, 1.0);
}