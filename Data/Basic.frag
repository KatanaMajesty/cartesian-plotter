#version 450 core

out vec4 color;

in vec4 o_Color;

void main()
{
	color = o_Color;
}