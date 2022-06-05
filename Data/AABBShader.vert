#version 450 core

layout (location = 0) in vec2 a_Position;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	gl_Position = u_Projection * u_View * vec4(a_Position.xy, 0.0, 1.0);
}