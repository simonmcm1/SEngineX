#version 150

in vec3 position;
in vec3 color;
in vec2 texCoord;
in vec3 normal;

out vec3 vColor;
out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vFragPosition;

uniform mat4 _MVP;
uniform mat4 _M;
uniform mat4 _VP;

void main()
{
    vColor = color;
    vTexCoord = texCoord;
    vNormal = mat3(transpose(inverse(_M))) * normal; //TODO: calc normal model once for all vertices
    gl_Position = _MVP * vec4(position, 1.0);
    vFragPosition = vec3(_M * vec4(position, 1.0));
}

