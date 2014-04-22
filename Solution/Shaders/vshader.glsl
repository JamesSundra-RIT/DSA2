#version 150

in vec4 vPosition;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 world;

void main()
{
	gl_Position = projection * view * world * vPosition;
}