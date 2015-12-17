#version 330 core

struct Material {
    sampler2D MainTex;
    sampler2D AltTex;
    vec3 Specular;
    float Shininess;
};

uniform Material material;


in vec3 vColor;
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPosition;
in vec4 vFragDirLightPosition;

out vec4 outColor;

#include lighting

void main()
{
    vec3 norm = normalize(vNormal);
    vec3 viewDir = normalize(Lights.ViewPos.xyz - vFragPosition);

	LightingResult lightresult = _Lighting(norm, viewDir, vFragPosition, material.Shininess);
    
    vec3 specular = material.Specular * lightresult.specular;
    vec3 objcolor = texture(material.MainTex, vTexCoord).xyz;
    
    vec3 result = (Lights.Ambient.xyz + lightresult.diffuse + specular) * objcolor.xyz;

    outColor = vec4(result, 1.0f);
    

    
}

