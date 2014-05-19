#version 330

//Alyssa Abraham

in vec4 vPosition; //Vertex Position
in vec3 vColor; //Vertex Color
in vec2 vUV; //Vertex UV
in vec3 normal; //Vertex normal
in vec3 tangent; //vertex tangent

out vec3 fColor; //Fragment Color (sent to the fragment shader)
out vec2 UV; //UVCoordinate
out vec3 norm; //normal coordinate
out vec3 tan; //tangent coordinate

uniform mat4 model; //model matrix
uniform mat4 view; //view matrix

uniform mat4 MVP; //Final Composed Matrix
uniform float d; //bump width
uniform float r; //roughness

uniform vec3 lightPosition; //light position
uniform vec3 eyePosition; //viewer position
uniform vec3 hiliteColor; //light color


//determine color based on wavelength
vec3 blend3(vec3 x)
{
	vec3 y = 1 - x * x;
	y = max(y, vec3(0.0));
	return y;
}

void main()
{
	vec3 P = vec3(view * vPosition); //position vector
	vec3 L = normalize(lightPosition - P); //light vector
	vec3 V = normalize(eyePosition - P); //viewer vector
	vec3 H = L + V; //halfway vector

	vec3 N = vec3(model * vec4(normal, 1.0)); //normal vector
	vec3 T = vec3(model * vec4(tangent, 1.0)); //tangent vector

	float u = abs(dot(T, H)) * d; //project onto tangent

	//calculate wavelength interference
	float w = dot(N, H);
	float e = r * u / w; 

	float c = exp(-e * e); //shape parameter- controls rainbow map

	vec4 anis = vec4(hiliteColor, 1.0) * vec4(c); //anisotropic highlight

	vec4 cdiff = vec4(0.0, 0.0, 0.0, 1.0); //diffraction color

	for(int m = 1; m < 8; m++)
	{
		float y = 2 * u / m - 1;
		cdiff += vec4(blend3(vec3(4 * (y-0.75), //red peak
			4 * (y - 0.5), //green peak
			4 * (y - 0.25))), //blue peak
			1.0);
	}

	gl_Position = MVP * vPosition;
	fColor = vec3(cdiff + anis);
	UV = vUV;
}