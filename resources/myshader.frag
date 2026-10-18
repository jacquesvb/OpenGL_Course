#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_position;

const vec3 WHITE = vec3(1.0, 1.0, 1.0);
const vec3 RED   = vec3(1.0, 0.0, 0.0);

const int STRIPE_COUNT = 10;

void main()
{
	// v_position.y runs from 1.0 at the top of the triangle down to -1.0 at the
	// bottom, so map that range onto STRIPE_COUNT equal horizontal bands
	// numbered from 0 at the top.
	float t = (1.0 - v_position.y) * 0.5 * float(STRIPE_COUNT); // 0 at the top, STRIPE_COUNT at the bottom
	int stripe = clamp(int(floor(t)), 0, STRIPE_COUNT - 1);     // the clamp keeps the bottom edge in the last stripe

	// Even stripes (0, 2, 4, ...) are white, odd stripes (1, 3, 5, ...) are red,
	// so the stripe at the very top of the triangle is white.
	out_color = (stripe % 2 == 0) ? vec4(WHITE, 1.0) : vec4(RED, 1.0);
}
