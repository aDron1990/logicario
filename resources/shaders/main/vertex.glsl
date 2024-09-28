#version 330 core

in vec2 inPos;
in vec2 inTexCoord;

out vec2 fragTexCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vec4(inPos.xy, 0.0, 1.0);
	fragTexCoord = inTexCoord;
}