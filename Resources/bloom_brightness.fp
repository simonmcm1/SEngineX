#version 330
layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 brightColor;
in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform float brightnessThreshold;

void main()
{             
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;

	outColor = vec4(hdrColor, 1.0);
	
	// Check whether fragment output is higher than threshold, if so output as brightness color
    float brightness = dot(hdrColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > brightnessThreshold)
         brightColor = vec4(hdrColor.rgb, 1.0);
	
}