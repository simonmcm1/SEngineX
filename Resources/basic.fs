#version 330 core

struct Material {
    sampler2D MainTex;
    sampler2D AltTex;
    vec3 Specular;
    float Shininess;
};

uniform Material material;

#include lighting

in vec3 vColor;
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPosition;

out vec4 outColor;

void main()
{
    vec3 norm = normalize(vNormal);
    vec3 viewDir = normalize(Lights.ViewPos.xyz - vFragPosition);

    LightingResult lightresult;
    lightresult.diffuse = vec3(0,0,0);
    lightresult.specular = vec3(0,0,0);
    
    for(int i = 0; i < Lights.NumberOfDirectionalLights; i++) {
        LightingResult dir = _Lighting_Directional(Lights.directionalLights[i], norm, viewDir);
        lightresult.diffuse += dir.diffuse;
        lightresult.specular += dir.specular;
    }
    
    for(int i = 0; i < Lights.NumberOfPointLights; i++) {
        LightingResult point = _Lighting_Point(Lights.pointLights[i], norm, vFragPosition, viewDir);
        lightresult.diffuse += point.diffuse;
        lightresult.specular += point.specular;
    }
    

    vec3 specular = material.Specular * lightresult.specular;
    vec3 objcolor = texture(material.MainTex, vTexCoord).xyz;
    
    vec3 result = (Lights.Ambient.xyz + lightresult.diffuse + specular) * objcolor.xyz;
    
    float gamma = 2.2;
    result = pow(result.rgb, vec3(1.0/gamma));
    
    outColor = vec4(result, 1.0f);
    

    
}

