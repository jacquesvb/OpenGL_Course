#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

out float v_height;

void main()
{

	gl_Position = vec4(in_position, 1);
	gl_Position.xyz *= 0.5;
	v_height = in_position.y;

}