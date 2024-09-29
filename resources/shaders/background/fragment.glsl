#version 330 core

in vec2 fragTexCoord;

out vec4 outColor;

uniform vec4 color;

void main()
{
    outColor = color;
    //outColor = vec4(1.0, 1.0, 1.0, 1.0);
}