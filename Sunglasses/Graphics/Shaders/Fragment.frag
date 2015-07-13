#version 330 core
struct Material {
    vec3 color;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

in vec3 outFragmentPosition;
in vec3 outNormal;
in vec2 outTextureCoordinates;

uniform vec3 viewPosition;

uniform Material material;

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
out vec4 color;

vec3 calculateDirectionalLight(DirectionalLight _directionalLight) {
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
    vec3 reflectionDirection = reflect(-lightDirection, outNormal);
    float specular = pow(max(dot(viewDirection, reflectionDirection), 0), 32);
    vec3 specularColor = material.color * _pointLight.specularColor * specular * specularConstant;
    
    float distance = length(_pointLight.position - outFragmentPosition);
    float attenuation = 1.0f / (_pointLight.constant + _pointLight.linear * distance + _pointLight.quadratic * (distance * distance));
    
    return (diffuseColor + specularColor) * attenuation;
}

void main() {
    vec3 ambient = material.color * vec3(0.015, 0.015, 0.015);
    
    vec3 result;
    result += ambient;
    
    result += calculateDirectionalLight(directionalLight);
    result += calculatePointLight(pointLight);
    
    color = vec4(result, 1.0);
}