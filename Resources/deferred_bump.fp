#version 330 core

struct Material {
    sampler2D MainTex;
    sampler2D AltTex;
	sampler2D Normals;
    vec3 Specular;
    float Shininess;
};

uniform Material material;

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPosition;

layout (location = 0) out vec3 gAlbedo;
layout (location = 1) out vec3 gPosition;
layout (location = 2) out vec3 gNormal;
layout (location = 3) out vec4 gSpec;


void main()
{
	gAlbedo = texture(material.MainTex, vTexCoord).xyz;
	gSpec = vec4(material.Specular, material.Shininess);
	gPosition = vFragPosition;
	vec3 normal = texture(material.Normals, vTexCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0); //transform to range [-1, 1]
	gNormal = normal;
}

