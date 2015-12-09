#version 330
out vec4 outColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform float exposure;

void main()
{             
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;

    // exposure
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    outColor = vec4(result, 1.0f);	
}