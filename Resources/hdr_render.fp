#version 330
out vec4 outColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform float exposure;

void main()
{             
	const float gamma = 1.5;
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
  
    // Exposure tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    // Gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
	outColor = vec4(mapped, 1.0);
}