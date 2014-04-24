#version 330

in vec2 UV;
in vec3 fColor;
out vec3 gl_Color;

uniform sampler2D TextureID;
uniform int nTexture = 0;

void main()
{
	if(nTexture == 0)
	{
		gl_Color = fColor;
	}
	else
	{
		gl_Color = texture2D( TextureID, UV ).rgb;
		gl_Color = gl_Color * fColor;
		gl_Color = clamp(gl_Color, 0.0, 1.0);
	}
}