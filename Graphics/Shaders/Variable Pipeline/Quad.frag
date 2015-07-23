#version 330 core

#ifdef OUTPUT_COLOR_0
layout (location = 0) out vec4 color;
#endif

#ifdef INPUT_POSITION
uniform sampler2D position;
#endif

#ifdef INPUT_NORMAL
uniform sampler2D normal;
#endif

#ifdef INPUT_COLOR
uniform sampler2D color;
#endif

in vertex_fragment {
    vec2 textureCoordinates;
} _input;

#ifdef LIGHTING
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

uniform PointLight pointLight;

vec3 calculateLighting(PointLight _pointLight, vec3 _position, vec3 _normal) {
    // Diffuse Lighting
    
    
    // Calculate the direction of the light to the fragment
    vec3 lightDirection = normalize(_pointLight.position - _position);
    
    // Calculate the dot product of the normal and the light direction, then choose 0 if lower than 0
    float diffuse = max(dot(_normal, lightDirection), 0.0);
    
    
    // Specular Lighting
    
    
    // Calculate the direction of the view to the fragment
    vec3 viewDirection = normalize(viewPosition - _position);
    
    // Calculate the halfway vector
    vec3 halfway = normalize(lightDirection + viewDirection);
    
    // Calculate the dot product of the normal and the halfway vector, then choose 0 if lower than 0, then raise to the shininess exponent
    float specular = pow(max(dot(_normal, halfway), 0.0), 128);
    
    // Return the diffuse value + the specular value
    return _pointLight.color * (diffuse + specular);
}
#endif

void main() {
    vec4 result;
    
    #ifdef LIGHTING_DEFERRED
    
    vec3 position = texture(position, _input.textureCoordinates).xyz;
    vec3 normal = texture(normal, _input.textureCoordinates).xyz;
    vec4 color = texture(color, _input.textureCoordinates).rgba;
    
    vec3 ambient = color * 0.1f;
    
    vec3 lighting = color * calculateLighting(pointLight);

    result = vec4(ambient + lighting, 1.0f);
    
    color = result;
    #endif
}