#version 150

in vec4 vPosition;

uniform mat4 perspective;
uniform mat4 world;

void main()
{
	gl_Position =  vPosition * world * perspective;
	//gl_Position = perspective * world * vPosition;
}