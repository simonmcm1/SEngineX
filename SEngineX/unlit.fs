#version 330 core

struct Material {
    vec3 color;
};

uniform Material material;

in vec3 vColor;
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vFragPosition;

out vec4 outColor;

void main()
{
    outColor = vec4(material.color, 1.0f);
}