
#ifdef OUTPUT_COLOR_0
layout (location = 0) out vec4 color;
#endif
#ifdef OUTPUT_AO_0
layout (location = 0) out float _occlusion;
#endif

#ifdef INPUT_POSITION
uniform sampler2D position;
#endif

#ifdef INPUT_NORMAL
uniform sampler2D normal;
#endif

#ifdef INPUT_COLOR
uniform sampler2D _color;
#endif

#ifdef INPUT_OCCLUSION
uniform sampler2D occlusion;
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
    bool attenuate;
};

uniform PointLight pointLight;

uniform vec3 viewPosition;
uniform vec3 viewDirection;

float constant = 1.0; 
float linear = 0.22;
float quadratic = 0.2;

vec3 calculateLighting(PointLight _pointLight, vec3 _position, vec3 _normal) {
    // Calculate Attenuation
    
    float attenuation = 1.0f;
    if (_pointLight.attenuate == true) {
        float distance = length(_pointLight.position - _position);
        attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));
    }
    
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
    float specular = pow(max(dot(_normal, halfway), 0.0), 1024);
    
    // Return the diffuse value + the specular value
    return _pointLight.color * (diffuse + specular) * attenuation;
}

float calculateDiffuse(PointLight _pointLight, vec3 _position, vec3 _normal) {
    // Calculate Attenuation
    
    float attenuation = 1.0f;
    if (_pointLight.attenuate == true) {
        float distance = length(_pointLight.position - _position);
        attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));
    }
    
    // Diffuse Lighting
    
    
    // Calculate the direction of the light to the fragment
    vec3 lightDirection = normalize(_pointLight.position - _position);
    
    // Calculate the dot product of the normal and the light direction, then choose 0 if lower than 0
    float diffuse = max(dot(_normal, lightDirection), 0.0);
    
    return diffuse * attenuation;
}

float calculateSpecular(PointLight _pointLight, vec3 _position, vec3 _normal) {
    // Calculate Attenuation
    
    float attenuation = 1.0f;
    if (_pointLight.attenuate == true) {
        float distance = length(_pointLight.position - _position);
        attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));
    }
    
    // Specular Lighting
    
    // Calculate the direction of the view to the fragment
    vec3 viewDirection = normalize(viewPosition - _position);
    
    // Calculate the direction of the light to the fragment
    vec3 lightDirection = normalize(_pointLight.position - _position);
    
    // Calculate the halfway vector
    vec3 halfway = normalize(lightDirection + viewDirection);
    
    // Calculate the dot product of the normal and the halfway vector, then choose 0 if lower than 0, then raise to the shininess exponent
    float specular = pow(max(dot(_normal, halfway), 0.0), 128);
    
    return specular * attenuation;
}
#endif

#ifdef CALCULATE_SSAO

uniform mat4 projection;
uniform mat4 view;
uniform sampler2D noise;
uniform vec3 samples[8];

const vec2 noiseScale = vec2(1600.0 / 4.0, 1200.0 / 4.0);

#endif

void main() {
    #ifdef LIGHTING_DEFERRED
    vec4 result;
    
    vec3 _position = texture(position, _input.textureCoordinates).rgb;
    vec3 normal = texture(normal, _input.textureCoordinates).rgb;
    vec3 __color = texture(_color, _input.textureCoordinates).rgb;
    
    #ifndef USE_SSAO
    vec3 ambient = __color * 0.3f;
    #endif
    #ifdef USE_SSAO
    vec3 ambient = __color * texture(occlusion, _input.textureCoordinates).r;
    #endif
    
    vec3 lighting = ambient + (__color * calculateLighting(pointLight, _position, normal));

    result = vec4(lighting, 1.0f);
    
    color = result;
    #endif
    
    #ifdef LIGHTING_DEFERRED_CEL
    vec4 result;
    
    vec3 _position = texture(position, _input.textureCoordinates).rgb;
    vec3 normal = texture(normal, _input.textureCoordinates).rgb;
    vec3 __color = texture(_color, _input.textureCoordinates).rgb;
    
    #ifndef USE_SSAO
    vec3 ambient = __color * 0.3f;
    #endif
    #ifdef USE_SSAO
    vec3 ambient = __color * texture(occlusion, _input.textureCoordinates).r;
    #endif
    
    const float diffuseSteps[4] = float[](0.1, 0.3, 0.6, 1.0);
    
    float diffuse = calculateDiffuse(pointLight, _position, normal);
    
    float E = fwidth(diffuse);
    
    if (diffuse > diffuseSteps[0] - E && diffuse < diffuseSteps[0] + E)
        diffuse = mix(diffuseSteps[0], diffuseSteps[1], smoothstep(diffuseSteps[0] - E, diffuseSteps[0] + E, diffuse));
    else if (diffuse > diffuseSteps[1] - E && diffuse < diffuseSteps[1] + E)
        diffuse = mix(diffuseSteps[1], diffuseSteps[2], smoothstep(diffuseSteps[1] - E, diffuseSteps[1] + E, diffuse));
    else if (diffuse > diffuseSteps[2] - E && diffuse < diffuseSteps[2] + E)
        diffuse = mix(diffuseSteps[2], diffuseSteps[3], smoothstep(diffuseSteps[2] - E, diffuseSteps[2] + E, diffuse));
    else if (diffuse < diffuseSteps[0])
        diffuse = 0.0;
    else if (diffuse < diffuseSteps[1])
        diffuse = diffuseSteps[1];
    else if (diffuse < diffuseSteps[2])
        diffuse = diffuseSteps[2];
    else
        diffuse = diffuseSteps[3];
    
    float specular = calculateSpecular(pointLight, _position, normal);
    
    E = fwidth(specular);
    if (specular > 0.5 - E && specular < 0.5 + E)
        specular = clamp(0.5 * (specular - 0.5 + E) / E, 0.0, 1.0);
    else
        specular = step(0.5, specular);
    
    vec3 lighting = ambient + (__color * (diffuse + specular));
    
    result = vec4(lighting, 1.0f);
    
    color = vec4(result);
    #endif
    
    #ifdef CALCULATE_SSAO
    
    vec3 _position = (view * vec4(texture(position, _input.textureCoordinates).rgb, 1.0)).rgb;
    vec3 normal = normalize(texture(normal, _input.textureCoordinates).rgb);
    vec3 random = texture(noise, _input.textureCoordinates * noiseScale).rgb;
    
    vec3 tangent = normalize(random - normal * dot(random, normal));
    vec3 bitangent = normalize(cross(normal, tangent));
    mat3 TBN = mat3(tangent, bitangent, normal);
    
    float __occlusion = 0.0;
    
    for (int i = 0; i < 8; ++i) {
        vec3 sample = TBN * samples[i];
        sample = _position + sample;
        
        vec4 offset = vec4(sample, 1.0);
        offset = projection * offset;
        offset.xyz /= offset.w;
        offset.xyz = offset.xyz * 0.5 + 0.5;
        
        float depth = -texture(position, offset.xy).w;
        
        float rangeCheck = smoothstep(0.0, 1.0, 1.0 / abs(_position.z - depth));
        __occlusion += (depth >= sample.z ? 1.0 : 0.0) * rangeCheck;
    }
    
    _occlusion = 1.0 - (__occlusion / 8.0);
    
    #endif
    
    #ifdef CALCULATE_BLUR_OCCLUSION
    
    vec2 texelSize = 1.0 / vec2(textureSize(occlusion, 0));
    float result;
    for (int x = -2; x < 2; x++) {
        for (int y = -2; y < 2; y++) {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            result += texture(occlusion, _input.textureCoordinates + offset).r;
        }
    }
    _occlusion = result / 16;

    #endif
}