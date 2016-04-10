// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#version 330 core

layout (location = 0) out vec4 color;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D _color;

uniform vec3 viewPosition;
uniform vec3 viewDirection;

in vertex_fragment {
    vec2 textureCoordinates;
} _input;

struct PointLight {
    // Color
    vec3 color;

    // Position
    vec3 position;

    // Attenuation
    bool attenuate;
};

struct ShadowPointLight {
	// Color
	vec3 color;

	// Position
	vec3 position;

	// Attenuation
	bool attenuate;

    // Far Plane
    float farPlane;

	// Shadow Map
	samplerCube shadowMap;
};

struct DirectionalLight {
	// Color
	vec3 color;

	// Direction
	vec3 direction;
};

struct ShadowDirectionalLight {
	// Color
	vec3 color;

	// Direction
	vec3 direction;

	// Shadow Map
	sampler2D shadowMap;

    // Light-Space Matrix
    mat4 lightMatrix;
};

uniform int pointLightCount;
uniform PointLight pointLights[32];

uniform int shadowPointLightCount;
uniform ShadowPointLight shadowPointLights[4];

uniform int directionalLightCount;
uniform DirectionalLight directionalLights[32];

uniform int shadowDirectionalLightCount;
uniform ShadowDirectionalLight shadowDirectionalLights[4];

float isShadowed(sampler2D shadow, vec3 position, vec3 normal, vec3 direction, mat4 matrix) {
	vec4 fragPosLightSpace = matrix * vec4(position, 1.0f);
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadow, projCoords.xy).r;
	float currentDepth = projCoords.z;
    /*float bias = 0.005f * tan(acos(clamp(dot(normal, direction), 0.0f, 1.0f)));
    bias = clamp(bias, 0.0f, 0.01f);*/
    float bias = max(0.05 * (1.0 - dot(normal, -direction)), 0.005);
	return currentDepth - bias > closestDepth ? 1.0 : 0.0;
}

float isShadowed(samplerCube cubemap, vec3 lightPosition, vec3 position, float farPlane) {
    vec3 fragmentToLight = position - lightPosition;
    float closestDepth = texture(cubemap, fragmentToLight).r;
    closestDepth *= farPlane;
    float currentDepth = length(fragmentToLight);
    float bias = 0.05f;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    return shadow;
}

vec3 calculateLighting(PointLight _pointLight, vec3 _position, vec3 _normal) {
    // Calculate Attenuation

    float attenuation = 1.0f;
    if (_pointLight.attenuate == true) {
        float distance = length(_pointLight.position - _position);
        //attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));
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
    float specular = pow(max(dot(_normal, halfway), 0.0), 128);

    // Return the diffuse value + the specular value
    return _pointLight.color * (diffuse + specular) * attenuation;
}

vec3 calculateLighting(ShadowPointLight _pointLight, vec3 _position, vec3 _normal) {
	if (isShadowed(_pointLight.shadowMap, _pointLight.position, _position, _pointLight.farPlane) == 0.0) {
		// Calculate Attenuation

  		float attenuation = 1.0f;
  		if (_pointLight.attenuate == true) {
  	    	float distance = length(_pointLight.position - _position);
  	    	//attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));
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
    	float specular = pow(max(dot(_normal, halfway), 0.0), 128);

    	// Return the diffuse value + the specular value
    	return _pointLight.color * (diffuse + specular) * attenuation;
	} else {
		return vec3(0.0f, 0.0f, 0.0f);
	}
}

vec3 calculateLighting(DirectionalLight _directionalLight, vec3 _position, vec3 _normal) {
	// Diffuse Lighting

    // Calculate the direction of the light to the fragment
    vec3 lightDirection = normalize(-_directionalLight.direction);

    // Calculate the dot product of the normal and the light direction, then choose 0 if lower than 0
    float diffuse = max(dot(_normal, lightDirection), 0.0);

    // Specular Lighting


    // Calculate the direction of the view to the fragment
    vec3 viewDirection = normalize(viewPosition - _position);

    // Calculate the halfway vector
    vec3 halfway = normalize(lightDirection + viewDirection);

    // Calculate the dot product of the normal and the halfway vector, then choose 0 if lower than 0, then raise to the shininess exponent
    float specular = pow(max(dot(_normal, halfway), 0.0), 16);

    // Return the diffuse value + the specular value
    return _directionalLight.color * (diffuse + specular);
}

vec3 calculateLighting(ShadowDirectionalLight _directionalLight, vec3 _position, vec3 _normal) {
	// Diffuse Lighting


    // Calculate the direction of the light to the fragment
    vec3 lightDirection = normalize(-_directionalLight.direction);

    // Calculate the dot product of the normal and the light direction, then choose 0 if lower than 0
    float diffuse = max(dot(_normal, lightDirection), 0.0);

    // Specular Lighting


    // Calculate the direction of the view to the fragment
    vec3 viewDirection = normalize(viewPosition - _position);

    // Calculate the halfway vector
    vec3 halfway = normalize(lightDirection + viewDirection);

    // Calculate the dot product of the normal and the halfway vector, then choose 0 if lower than 0, then raise to the shininess exponent
    float specular = pow(max(dot(_normal, halfway), 0.0), 16);

    // Return the diffuse value + the specular value
    return _directionalLight.color * (diffuse + specular);
}

float calculateDiffuse(PointLight _pointLight, vec3 _position, vec3 _normal) {
    // Calculate Attenuation

    float attenuation = 1.0f;
    if (_pointLight.attenuate == true) {
        float distance = length(_pointLight.position - _position);
        //attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));
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
        //attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));
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

void main() {
    vec4 result;

    vec3 _position = texture(position, _input.textureCoordinates).rgb;
    vec3 normal = texture(normal, _input.textureCoordinates).rgb;
    vec3 _color_ = texture(_color, _input.textureCoordinates).rgb;

    #ifndef USE_SSAO
    vec3 ambient = _color_ * 0.025f;
    #endif
    #ifdef USE_SSAO
    vec3 ambient = _color_ * texture(occlusion, _input.textureCoordinates).r;
    #endif

    vec3 lighting = ambient;

    // Lighting: Point Lights
    for (int i = 0; i < pointLightCount; i++) {
        lighting += _color_ * calculateLighting(pointLights[i], _position, normal);
    }

	// Lighting: Shadowed Point Lights
	for (int i = 0; i < shadowPointLightCount; i++) {
		lighting += _color_ * calculateLighting(shadowPointLights[i], _position, normal);
	}

	// Lighting: Directional Lights
	for (int i = 0; i < directionalLightCount; i++) {
		/*lighting += (1.0 - isShadowed(shadowMap, _position, normal, directionalLights[i].direction)) * _color_ * calculateLighting(directionalLights[i], _position, normal);*/
        lighting += _color_ * calculateLighting(directionalLights[i], _position, normal);
	}

    // Lighting: Shadow Directional Lights
    for (int i = 0; i < shadowDirectionalLightCount; ++i) {
        lighting += (1.0 - isShadowed(shadowDirectionalLights[i].shadowMap, _position, normal, shadowDirectionalLights[i].direction, shadowDirectionalLights[i].lightMatrix)) * _color_ * calculateLighting(shadowDirectionalLights[i], _position, normal);
    }

    result = vec4(lighting, 1.0f);
    color = result;
}
