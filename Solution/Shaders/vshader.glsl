#version 330

in vec4 vPosition; //Vertex Position
in vec3 vColor; //Vertex Color
in vec2 vUV; //Vertex UV
in vec3 normal;
in vec3 tangent;

out vec3 fColor; //Fragment Color (sent to the fragment shader)
out vec2 UV; //UVCoordinate
out vec3 norm;
out vec3 tan;

uniform mat4 model;
uniform mat4 view;

uniform mat4 MVP; //Final Composed Matrix
uniform float d; //bump width
uniform float r; //roughness
uniform vec3 lightPosition;
uniform vec3 eyePosition;
uniform vec3 hiliteColor;


vec3 lambda2rgb(float lambda)
{
	const float ultrav = 400.0; //wavelength of ultraviolet light
	const float infra = 700.0; //wavelength of infrared light

	float a = (lambda - ultrav) / (infra - ultrav);

	vec3 bump = (vec3(a) - vec3(0.75, 0.5, 0.25));
	vec3 color = (1.0 - d) * bump * bump;
	return color;
}


void main()
{
	vec3 P = vec3(view * vPosition); //position vector
	vec3 L = normalize(lightPosition - P); //light vector
	vec3 V = normalize(eyePosition - P); //viewer vector
	vec3 H = L + V; //halfway vector
	
	//calculate interference
	vec3 T = vec3(model * vec4(tangent, 1.0)); //tangent vector
	float u = abs(dot(T, H));
	vec3 cdiff = vec3(0.0);
	for(int m = 1; m <= 3; m++) //
	{
		float lambda = r * u / float(m); //calculate wavelength
		cdiff += lambda2rgb(lambda);
	}

	//calculate color of highlight
	vec3 N = vec3(model * vec4(normal, 1.0)); //normal vector
	float w = dot(N, H);
	float e = r * u /w;
	vec3 hilight = exp(-e * e) * hiliteColor;

	gl_Position = MVP * vPosition;
	fColor = vec3(0.8 * cdiff + hilight);
	UV = vUV;
}