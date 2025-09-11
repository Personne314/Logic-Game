#version 450 core



in vec2 relative_pos;	// Coordinate from the vertex shader.
flat in uint bus_type;	// Type of the current bus section.

out vec4 out_color;	// Final color of the fragment.

uniform uint size;	// Number of wire in the bus.
uniform uint state;	// State of the bus. 
uniform vec4 off_color;	// Color of off wire in the bus.
uniform vec4 on_color;	// Color of on wire in the bus.
uniform vec4 inner_color;	// Color of inner part of a node.
uniform vec4 outer_color;	// Color of outer part of a node.



void main()
{

	// Absolute value of the distance.
	vec2 abs_pos = abs(relative_pos);
	
	// Get the used directions.
	bool up    = (bus_type & 0x1) != 0;
	bool left  = (bus_type & 0x2) != 0;
	bool down  = (bus_type & 0x4) != 0;
	bool right = (bus_type & 0x8) != 0;

	// Check if the directions are to be inverted (used for rotations).
	bool inverse = (bus_type & 0x10) != 0;

	// Number of autorized documents.
	int nb_dir = int(up) + int(left) + int(down) + int(right);

	// Default color.
	out_color = vec4(0,0,0,0);
	


	if (nb_dir == 2) {

		if (left && right) {



		} else if (up && down) {



		// Render the center in case of a curve.
		} else {

			// Get the center of the circle.
			vec2 center = vec2(0,0);
			if (up && left) center = vec2(-1, 1);
			if (up && right) center = vec2(1, 1);
			if (down && left) center = vec2(-1, -1);
			if (down && right) center = vec2(1, -1);

			// Draw the circle.
			float norm_dist = length(relative_pos-center)/2;
			uint i = uint(floor(norm_dist * size));			
			if (i < size) {
				if (inverse) i = size-i-1;
				if ((state & (1 << i)) != 0) out_color = on_color;
				else out_color = off_color;
			}
			
		}

	} else {
		if (abs_pos.x < 0.75 && abs_pos.y < 0.75) out_color = inner_color;
		else out_color = outer_color;
	}

}
