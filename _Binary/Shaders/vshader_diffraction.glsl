#version 330

in vec4 vPosition; //Vertex Position
in vec3 vColor; //Vertex Color
in vec2 vUV; //Vertex UV
in vec3 normal;
in vec3 tangent;

out vec3 fColor; //Fragment Color (sent to the fragment shader)
out vec2 UV; //UVCoordinate

uniform float r;
uniform float d;
uniform mat4 model;
uniform mat4 view;
uniform mat4 MVP; //Final Composed Matrix
uniform vec4 hiliteColor;
uniform vec3 lightPosition;
uniform vec3 eyePosition;

/*vec3 blend3(vec3 x)
{
	vec3 y = 1 - x * x;
	y = max(y, vec3(0, 0, 0));
	return y;
}

void diffraction()
{
	vec3 P = view * vPosition;
	vec3 L = normalize(lightPosition - P);
	vec3 V = normalize(eyePosition - P);
	vec3 H = L + V;
	vec3 N = model * normal;
	vec3 T = model * tangent;
	float u = dot(T, H) * d;
	float w = dot(N, H);
	float e = r * u/w;
	float c = exp(-e * e);
	vec4 anis vec4(c, c, c, 1.0);
}*/

void main()
{
	gl_Position = MVP * vPosition;
	fColor = vColor;
	UV = vUV;
}
