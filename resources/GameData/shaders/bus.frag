#version 450 core

#define WIDTH 0.4



in vec2 relative_pos;	// Coordinate from the vertex shader.
flat in uint bus_type;	// Type of the current bus section.

out vec4 out_color;	// Final color of the fragment.

uniform uint size;
uniform uint state;
uniform vec4 off_color;	// Color of off wire in the bus.
uniform vec4 on_color;	// Color of on wire in the bus.



void main()
{

	vec2 abs_pos = abs(relative_pos);
	
	// Get the used directions.
	bool up    = (bus_type & 0x1) != 0;
	bool left  = (bus_type & 0x2) != 0;
	bool down  = (bus_type & 0x4) != 0;
	bool right = (bus_type & 0x8) != 0;

	// Check if the directions are inputs or outputs.
	bool in_up    = (bus_type & 0x10) != 0;
	bool in_left  = (bus_type & 0x20) != 0;
	bool in_down  = (bus_type & 0x40) != 0;
	bool in_right = (bus_type & 0x80) != 0;


	
	// Default color.
	out_color = vec4(0,0,0,0);
	
	// Center.
	if (abs_pos.x <= WIDTH && abs_pos.y <= WIDTH) {
		out_color = vec4(0,0,0,1);
	}

	// Up.
	if (up && abs_pos.x <= WIDTH && relative_pos.y > WIDTH) {
		float norm_pos = (relative_pos.x + WIDTH) / (2.0 * WIDTH);
		uint i = uint(floor(norm_pos * size));
		if (!in_up) i = size-i-1;
		if ((state & (1 << i)) != 0) out_color = on_color;
		else out_color = off_color;
	}

	// Left.
	if (left && abs_pos.y <= WIDTH && relative_pos.x < -WIDTH) {
		float norm_pos = (relative_pos.y + WIDTH) / (2.0 * WIDTH);
		uint i = uint(floor(norm_pos * size));
		if (!in_left) i = size-i-1;
		if ((state & (1 << i)) != 0) out_color = on_color;
		else out_color = off_color;
	}

	// Down.
	if (down && abs_pos.x <= WIDTH && relative_pos.y < -WIDTH) {
		float norm_pos = (relative_pos.x + WIDTH) / (2.0 * WIDTH);
		uint i = uint(floor(norm_pos * size));
		if (in_down) i = size-i-1;
		if ((state & (1 << i)) != 0) out_color = on_color;
		else out_color = off_color;
	}

	// Right.
	if (right && abs_pos.y <= WIDTH && relative_pos.x > WIDTH) {
		float norm_pos = (relative_pos.y + WIDTH) / (2.0 * WIDTH);
		uint i = uint(floor(norm_pos * size));
		if (in_right) i = size-i-1;
		if ((state & (1 << i)) != 0) out_color = on_color;
		else out_color = off_color;
	}

}
