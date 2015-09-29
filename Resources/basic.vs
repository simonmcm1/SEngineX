#version 330

layout (location = 0) in vec3 position;

layout (location = 3) in vec3 color;

layout (location = 2) in vec2 texCoord;

layout (location = 1) in vec3 normal;

out vec3 vColor;
out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vFragPosition;
out vec4 vFragDirLightPosition;

//TODO: move other internal blocks to the UBO
uniform mat4 _MVP;
uniform mat4 _M;
uniform mat4 _VP;
uniform vec2 _tiling;
uniform mat4 _DirLightSpace;

void main()
{
    vColor = color;
    vTexCoord = vec2(texCoord.x * _tiling.x, texCoord.y * _tiling.y);
    vNormal = mat3(transpose(inverse(_M))) * normal; //TODO: calc normal model once for all vertices
    gl_Position = _MVP * vec4(position, 1.0);
	vec3 fragPos = vec3(_M * vec4(position, 1.0));
    vFragPosition = vec3(_M * vec4(position, 1.0));
    vFragDirLightPosition = _DirLightSpace * vec4(fragPos, 1.0); //Lights.DirLightSpace * vec4(vFragPosition, 1.0);
}

