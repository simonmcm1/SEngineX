#version 150

uniform vec3 _Color;
uniform sampler2D _MainTex;
uniform sampler2D _AltTex;

in vec3 vColor;
in vec2 vTexCoord;

out vec4 outColor;

void main()
{
    outColor = mix(texture(_MainTex, vTexCoord), texture(_AltTex, vTexCoord), 0.2);
}

