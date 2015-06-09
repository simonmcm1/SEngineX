#version 150

struct Material {
    sampler2D MainTex;
    sampler2D AltTex;
    vec3 Specular;
    float Shininess;
};

struct DirectionalLight {
    vec4 color;
    vec4 direction;
};

struct PointLight {
    vec4 position;
    vec4 color;
    float constant;
    float linear;
    float quadratic;
	
    
};

#define NR_POINT_LIGHTS 4

layout (std140) uniform InternalData
{
    vec4 Ambient;
    vec4 ViewPos;
    PointLight pointLights[4];
    DirectionalLight directionalLights[2];
} Lights;

struct LightingResult {
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;

in vec3 vColor;
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPosition;

out vec4 outColor;

//TODO: move internal/lighting calcs into include file

LightingResult _Lighting_Directional(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    LightingResult result;
    
    vec3 lightDir = normalize(-light.direction.xyz);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
    
    result.diffuse = light.color.xyz * diff;
    result.specular = light.color.xyz * spec;
    
    return result;
}

// Calculates the color when using a point light.
LightingResult _Lighting_Point(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    LightingResult result;
    
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir.xyz, reflectDir), 0.0), material.Shininess);
    // Attenuation
    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Combine results
    
    result.diffuse = light.color.xyz * diff * attenuation;
    result.specular = light.color.xyz * spec * attenuation;
    
    return result;
}


void main()
{
    vec3 norm = normalize(vNormal);
    vec3 viewDir = normalize(Lights.ViewPos.xyz - vFragPosition);

    LightingResult lightresult = _Lighting_Directional(Lights.directionalLights[0], norm, viewDir);
    
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        LightingResult point = _Lighting_Point(Lights.pointLights[i], norm, vFragPosition, viewDir);
        lightresult.diffuse += point.diffuse;
        lightresult.specular += point.specular;
    }
    

    vec3 specular = material.Specular * lightresult.specular;
    vec3 objcolor = texture(material.MainTex, vTexCoord).xyz;
    
    vec3 result = (Lights.Ambient.xyz + lightresult.diffuse + specular) * objcolor.xyz;
    outColor = vec4(result, 1.0f);
    
    //outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    //outColor = vec4(Lights.directionalLights[0].color.xyz, 1.0f);
    
    
}

