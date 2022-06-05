#version 450 core

out vec4 color;

uniform bool u_Collides;

void main()
{
	vec3 rgb = vec3(0.3, 0.9, 0.6);
	if (u_Collides)
	{
		rgb = vec3(1.0, 0.3, 0.2);
	}
	color = vec4(rgb.rgb, 1.0);
}