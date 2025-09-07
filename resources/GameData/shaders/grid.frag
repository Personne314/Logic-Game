#version 450 core

in vec2 grid_pos;	// Coordinate from the vertex shader.

out vec4 out_color;	// Fincal color of the fragment.


#define MAJOR_WIDTH  0.02 // Width of the major lines
#define MINOR_WIDTH  0.015 // Width of the minor lines
#define BACKGROUND_COLOR vec4(0.1, 0.1, 0.12, 1.0)	// Color of the background.
#define MAJOR_COLOR vec4(0.2, 0.4, 0.4, 1.0)	// Color of the major lines.
#define MINOR_COLOR vec4(0.2, 0.25, 0.3, 1.0)	// Color of the minor lines.

void main()
{
    
	// Check for lines.
    vec2 major_dist = 5.0 * abs(fract(grid_pos / 5.0 + 0.5) - 0.5);
    vec2 minor_dist = abs(fract(grid_pos + 0.5) - 0.5);

    // Apply background color.
    out_color = BACKGROUND_COLOR;
    
    // Color minor lines.
    if (minor_dist.x < MINOR_WIDTH || minor_dist.y < MINOR_WIDTH) {
        out_color = MINOR_COLOR;
    }

	// Color major lines.
    if (major_dist.x < MAJOR_WIDTH || major_dist.y < MAJOR_WIDTH) {
        out_color = MAJOR_COLOR;
    }

}