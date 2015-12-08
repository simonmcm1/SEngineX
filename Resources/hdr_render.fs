#version 330
out vec4 outColor;
in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform float exposure;

void main()
{             
    const float gamma = 2.2;
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;

    // reinhard
    // vec3 result = hdrColor / (hdrColor + vec3(1.0));
    // exposure
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
 //   result = pow(result, vec3(1.0 / gamma));
    outColor = vec4(result, 1.0f);
	//outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}