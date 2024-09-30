#version 330 core

in vec2 fragTexCoord;

out vec4 outColor;

uniform sampler2D inTexture;

void main()
{
    outColor = texture(inTexture, fragTexCoord);
}