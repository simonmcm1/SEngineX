#version 150

in vec3 position;
in vec3 color;
in vec2 texCoord;

out vec3 vColor;
out vec2 vTexCoord;

uniform mat4 _MVP;

void main()
{
    vColor = color;
    vTexCoord = texCoord;
    gl_Position = _MVP * vec4(position, 1.0);
}

