
struct DirectionalLight {
    vec4 color;
    vec4 direction;
};

struct PointLight {
    vec4 position;
    vec4 color;
    float constant;
    float linear;
    float quadratic;
 //   float pad;
};

#define NR_POINT_LIGHTS 4

layout (std140) uniform InternalData
{
    vec4 Ambient;
    vec4 ViewPos;
    PointLight pointLights[4];
    DirectionalLight directionalLights[2];
    float NumberOfPointLights;
    float NumberOfDirectionalLights;
    mat4 DirLightSpace;
} Lights;

struct LightingResult {
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D _DirLightDepth;
uniform mat4 _DirLightSpace;

float DirShadowCalculation(vec4 fragPosLightSpace, float bias)
{
  //perspective divide
   vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(_DirLightDepth, projCoords.xy).r;
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Check whether current frag pos is in shadow

	//PCF
	float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(_DirLightDepth, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(_DirLightDepth, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

LightingResult _Lighting_Directional(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float shininess)
{
    LightingResult result;
    
    vec3 lightDir = normalize(-light.direction.xyz);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    	
	vec4 fragPosLightSpace = _DirLightSpace * vec4(fragPos, 1.0);
	float bias = max(0.00001 * (1.0 - dot(normal, lightDir)), 0.00001);  
    float shadow = DirShadowCalculation(fragPosLightSpace, bias);
    
    result.diffuse = light.color.xyz * diff * (1.0 - shadow);
    result.specular = light.color.xyz * spec * (1.0 - shadow);
    
    return result;
}

// Calculates the color when using a point light.
LightingResult _Lighting_Point(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float shininess)
{
    LightingResult result;
    
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    
    // Attenuation
    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Combine results
    
    result.diffuse = light.color.xyz * diff * attenuation;
    result.specular = light.color.xyz * spec * attenuation;
    
    return result;
}

LightingResult _Lighting(vec3 norm, vec3 viewDir, vec3 fragPosition, float shininess)
{
    LightingResult lightresult;
    lightresult.diffuse = vec3(0,0,0);
    lightresult.specular = vec3(0,0,0);
    
    for(int i = 0; i < Lights.NumberOfDirectionalLights; i++) {
        LightingResult dir = _Lighting_Directional(Lights.directionalLights[i], norm, fragPosition, viewDir, shininess);
        lightresult.diffuse += dir.diffuse;
        lightresult.specular += dir.specular;
    }
    
      for(int i = 0; i < Lights.NumberOfPointLights; i++) {
        LightingResult point = _Lighting_Point(Lights.pointLights[i], norm, fragPosition, viewDir, shininess);
        lightresult.diffuse += point.diffuse;
        lightresult.specular += point.specular;
    }
	
	return lightresult;
}

