#version 150

struct Material {
    sampler2D MainTex;
    sampler2D AltTex;
    vec3 Specular;
    float Shininess;
};

struct DirectionalLight {
    vec3 color;
    vec3 direction;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 color;
};

#define NR_POINT_LIGHTS 4

struct Internal {
    vec3 Ambient;
    vec3 ViewPos;
    PointLight pointLights[NR_POINT_LIGHTS];
    DirectionalLight directionalLight;
};

struct LightingResult {
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Internal internal;

in vec3 vColor;
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPosition;

out vec4 outColor;

//TODO: move internal/lighting calcs into include file

LightingResult _Lighting_Directional(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    LightingResult result;
    
    vec3 lightDir = normalize(-light.direction);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
    
    result.diffuse = light.color * diff;
    result.specular = light.color * spec;
    
    return result;
}

// Calculates the color when using a point light.
LightingResult _Lighting_Point(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    LightingResult result;
    
    vec3 lightDir = normalize(light.position - fragPos);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Combine results
    
    result.diffuse = light.color * diff * attenuation;
    result.specular = light.color * spec * attenuation;
    
    return result;
}


void main()
{
    vec3 norm = normalize(vNormal);
    vec3 viewDir = normalize(internal.ViewPos - vFragPosition);

    LightingResult lightresult = _Lighting_Directional(internal.directionalLight, norm, viewDir);
    
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        LightingResult point = _Lighting_Point(internal.pointLights[i], norm, vFragPosition, viewDir);
        lightresult.diffuse += point.diffuse;
        lightresult.specular += point.specular;
    }
    

    vec3 specular = material.Specular * lightresult.specular;
    vec3 objcolor = texture(material.MainTex, vTexCoord).xyz;
    
    vec3 result = (internal.Ambient + lightresult.diffuse + specular) * objcolor.xyz;
    outColor = vec4(result, 1.0f);
    
    
}

