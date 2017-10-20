#version 330
out vec2 texcoord;
uniform mat4 MVP;
in vec3 _position;
in vec2 _texcoord;

void main()
{
    gl_Position = MVP * vec4(_position, 1.0);
    texcoord = _texcoord;
}
