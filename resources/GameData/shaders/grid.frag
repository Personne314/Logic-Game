#version 450 core

#define MAJOR_WIDTH  0.02 // Width of the major lines
#define MINOR_WIDTH  0.015 // Width of the minor lines



in vec2 grid_pos;	// Coordinate from the vertex shader.

out vec4 out_color;	// Final color of the fragment.

uniform vec4 background_color;	// Color of the background.
uniform vec4 major_color;	// Color of the major lines.
uniform vec4 minor_color;	// Color of the minor lines.



void main()
{

	// Check for lines.
	vec2 major_dist = 5.0 * abs(fract(grid_pos / 5.0 + 0.5) - 0.5);
	vec2 minor_dist = abs(fract(grid_pos + 0.5) - 0.5);

	// Interpolate the distance using smoothstep.
	float minor_line = 1.0 - smoothstep(0.0, MINOR_WIDTH, min(minor_dist.x, minor_dist.y));
	float major_line = 1.0 - smoothstep(0.0, MAJOR_WIDTH, min(major_dist.x, major_dist.y));

	// Calculate the final color.
	out_color = 
		background_color * (1.0 - max(minor_line, major_line)) 
		+ minor_color * minor_line * (1.0 - major_line) 
		+ major_color * major_line;
	
}
