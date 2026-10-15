#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_position;

const vec3 RED       = vec3(1.0, 0.0, 0.0);
const vec3 GREEN     = vec3(0.0, 1.0, 0.0);
const vec3 DARK_BLUE = vec3(0.0, 0.0, 0.5);

void main()
{
	// Top half of the triangle (y >= 0): solid red, no gradient.
	if (v_position.y >= 0.0)
	{
		out_color = vec4(RED, 1.0);
		return;
	}

	// Bottom half: green on the left, dark blue on the right. The two colours
	// blend into each other as they approach the vertical axis (x = 0).
	float halfWidth = (1.0 - v_position.y) * 0.5;             // triangle half-width at this height
	float u = clamp(v_position.x / halfWidth, -1.0, 1.0);     // -1 = left edge, 0 = axis, +1 = right edge
	float mixFactor = u * 0.5 + 0.5;                          // 0 = green, 1 = dark blue

	// Near the bottom edge of the red section the green and dark blue blend a
	// little more, so the left/right corners only stay pure down at the bottom.
	float towardRed = clamp(v_position.y + 1.0, 0.0, 1.0);    // 0 at the bottom, 1 at the red edge
	mixFactor = mix(mixFactor, 0.5, towardRed * 0.5);

	out_color = vec4(mix(GREEN, DARK_BLUE, mixFactor), 1.0);
}

