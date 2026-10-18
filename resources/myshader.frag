#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_position;

const vec3 CYAN    = vec3(0.0, 1.0, 1.0); // vertex 1: top
const vec3 MAGENTA = vec3(1.0, 0.0, 1.0); // vertex 2: bottom-left
const vec3 YELLOW  = vec3(1.0, 1.0, 0.0); // vertex 3: bottom-right

void main()
{
	// Barycentric weights of the big triangle: each one is 1.0 at its own
	// corner, 0.0 on the opposite edge, and the three always sum to 1.
	float wTop   = (v_position.y + 1.0) * 0.5;                        // 1 at ( 0,  1)
	float wLeft  = (1.0 - 2.0 * v_position.x - v_position.y) * 0.25;  // 1 at (-1, -1)
	float wRight = (1.0 + 2.0 * v_position.x - v_position.y) * 0.25;  // 1 at ( 1, -1)

	// Blend the three corner colors: each is strongest at its own vertex and
	// falls off linearly toward the opposite edge, so cyan, magenta and yellow
	// all meet and mix toward the middle of the triangle.
	out_color = vec4(wTop * CYAN + wLeft * MAGENTA + wRight * YELLOW, 1.0);
}
