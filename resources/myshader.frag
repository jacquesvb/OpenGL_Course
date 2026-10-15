#version 330 core

layout(location = 0) out vec4 out_color;

in float v_height;

void main()
{
	// v_height is -1 at the bottom and +1 at the top of the triangle.
	// Remap it to 0..1 so the top is white and the bottom is black.
	float t = v_height * 0.5 + 0.5;

	out_color = vec4(vec3(t), 1);
}

