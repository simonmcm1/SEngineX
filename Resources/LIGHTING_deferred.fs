#version 330 core

out vec4 outColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gSpecular;

#include lighting

void main()
{
    vec3 norm = normalize(texture(gNormal, TexCoords).rgb);
	vec3 fragPosition = texture(gPosition, TexCoords).rgb;
	vec3 albedo = texture(gAlbedo, TexCoords).rgb;
	vec4 spec = texture(gSpecular, TexCoords);
	vec3 specColor = spec.rgb;
	float shininess = spec.a;
	
    vec3 viewDir = normalize(Lights.ViewPos.xyz - fragPosition);

    LightingResult lightresult;
    lightresult.diffuse = vec3(0,0,0);
    lightresult.specular = vec3(0,0,0);
    
    for(int i = 0; i < Lights.NumberOfDirectionalLights; i++) {
        LightingResult dir = _Lighting_Directional(Lights.directionalLights[i], norm, viewDir, shininess);
        lightresult.diffuse += dir.diffuse;
        lightresult.specular += dir.specular;
    }
    
      for(int i = 0; i < Lights.NumberOfPointLights; i++) {
        LightingResult point = _Lighting_Point(Lights.pointLights[i], norm, fragPosition, viewDir, shininess);
        lightresult.diffuse += point.diffuse;
        lightresult.specular += point.specular;
    }
    

    vec3 specular = specColor * lightresult.specular;   
    vec3 result = (Lights.Ambient.xyz + lightresult.diffuse + specular) * albedo;
    
    outColor = vec4(result, 1.0f);
	//outColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}

