#version 330
out vec4 outColor;
out vec4 brightColor;
in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform sampler2D brightnessBuffer;

void main()
{             
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;      
    vec3 bloomColor = texture(brightnessBuffer, TexCoords).rgb;
    hdrColor += bloomColor; // additive blending
	outColor = vec4(hdrColor, 1.0f);
}  