#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_position;

const vec3 WHITE = vec3(1.0, 1.0, 1.0);
const vec3 RED   = vec3(1.0, 0.0, 0.0);

const float ROW_COUNT = 10.0;

void main()
{
	// Split the triangle into ROW_COUNT rows (y goes from 1.0 at the top to
	// -1.0 at the bottom).
	float rowCoord = (1.0 - v_position.y) * 0.5 * ROW_COUNT;
	float row = min(floor(rowCoord), ROW_COUNT - 1.0); // 0 = top row; the min keeps the bottom edge inside the last row
	float f = rowCoord - row;                          // 0 at the top of the row, 1 at its bottom

	// Horizontal coordinate of the triangular lattice: the centre of a
	// point-up triangle sits on an even m, the centre of a point-down
	// (inverted) triangle on an odd m.
	float m = v_position.x * ROW_COUNT + row;

	// Distance to the nearest even m: 0 at the centre of a point-up triangle,
	// 1 at the centre of a point-down one.
	float d = abs(m - 2.0 * round(m * 0.5));

	// A point-up triangle starts as an apex point at the top of its row and
	// widens downward (d < f); a point-down triangle starts wide and narrows
	// to an apex. Testing d against f therefore reads white, red, white,
	// red, ... across every row.
	out_color = (d < f) ? vec4(WHITE, 1.0) : vec4(RED, 1.0);
}
