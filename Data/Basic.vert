#version 450 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec4 a_Color;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

uniform vec4 u_SelectedColor;
uniform bool u_Selected;

out vec4 o_Color;

void main()
{
	o_Color = a_Color;
	if (u_Selected)
	{
		o_Color = a_Color * vec4(u_SelectedColor.xyz, 1.0);
	}
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position.xy, 0.0, 1.0);
}