#version 330
out vec4 FragColor;

in vec2 texcoord;
uniform sampler2D textureSampler;

void main()
{
    FragColor = texture(textureSampler, texcoord);
}
