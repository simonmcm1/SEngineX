#version 330

layout (location = 0) in vec3 position;

//TODO: move other internal blocks to the UBO
uniform mat4 _MVP;
uniform mat4 _M;
uniform mat4 _VP;
uniform vec2 _tiling;

void main()
{
    gl_Position = _MVP * vec4(position, 1.0);
}
