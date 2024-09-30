#version 330 core

in vec2 inPos;

uniform mat4 view;

void main()
{
	gl_Position = view * vec4(inPos.xy, 0.0, 1.0);
}