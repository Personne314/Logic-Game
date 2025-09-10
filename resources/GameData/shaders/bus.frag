#version 450 core

#define MAJOR_WIDTH  0.02 // Width of the major lines
#define MINOR_WIDTH  0.015 // Width of the minor lines



in vec2 relative_pos;	// Coordinate from the vertex shader.

out vec4 out_color;	// Final color of the fragment.

uniform vec4 off_color;
uniform vec4 on_color;



void main()
{
	out_color = off_color;
	if (relative_pos.x > 0 && relative_pos.y > 0) out_color = vec4(0,0,0,1);

}
