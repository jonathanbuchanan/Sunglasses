#version 330 core
out vec4 fragmentColor;

in vec2 outTextureCoordinates;

uniform vec3 viewPosition;

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D g_color;

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

/*vec3 calculateLighting(DirectionalLight _directionalLight) {
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
}*/

void main() {
    vec3 position = vec3(texture(g_position, outTextureCoordinates));
    vec3 normal = vec3(texture(g_normal, outTextureCoordinates));
    vec3 albedo = texture(g_color, outTextureCoordinates).rgb;
    float specular = texture(g_color, outTextureCoordinates).a;
    
    // Ambient Lighting
    vec3 ambient = albedo * 0.1f;
    
    vec3 lighting = albedo * calculateLighting(pointLight, position, normal);
    
    fragmentColor = vec4(ambient + lighting, 1.0f);
}