#version 150

in vec4 vPosition; //Vertex position

uniform mat4 worldMatrix; //World Matrix

uniform mat4 viewMatrix; //Camera Matrix

uniform mat4 projMatrix; //Projection Matrix


void
main()
{
	gl_Position = worldMatrix * vPosition;
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projMatrix * gl_Position;
}
