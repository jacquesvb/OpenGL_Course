#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_position;

const vec3 RED   = vec3(1.0, 0.0, 0.0);
const vec3 GREEN = vec3(0.0, 1.0, 0.0);
const vec3 BLUE  = vec3(0.0, 0.0, 1.0);

void main()
{
	// Barycentric coordinates of the big triangle: each one is 1.0 at its own
	// corner and 0.0 on the edge opposite that corner, and they always sum to 1.
	float cornerTop   = (v_position.y + 1.0) * 0.5;                        // 1 at ( 0,  1)
	float cornerLeft  = (1.0 - 2.0 * v_position.x - v_position.y) * 0.25;  // 1 at (-1, -1)
	float cornerRight = (1.0 + 2.0 * v_position.x - v_position.y) * 0.25;  // 1 at ( 1, -1)

	// Each corner colour owns the region where its coordinate reaches 0.5, i.e.
	// everything on its side of the midpoints of the two edges meeting there:
	//
	//   - cornerTop >= 0.5  -> top half of the triangle (y >= 0): red
	//   - cornerLeft >= 0.5 -> bottom-left corner: green
	//   - cornerRight >= 0.5 -> bottom-right corner: blue
	//
	// Those three regions leave an inverted triangle in the middle.
	if (cornerTop >= 0.5)
	{
		out_color = vec4(RED, 1.0);
	}
	else if (cornerLeft >= 0.5)
	{
		out_color = vec4(GREEN, 1.0);
	}
	else if (cornerRight >= 0.5)
	{
		out_color = vec4(BLUE, 1.0);
	}
	else
	{
		// Middle inverted triangle: a smooth blend of the three corner colours,
		// weighted by the barycentric coordinates, so it leans red near the top
		// edge, green near the left edge and blue near the right edge.
		out_color = vec4(cornerTop * RED + cornerLeft * GREEN + cornerRight * BLUE, 1.0);
	}
}
