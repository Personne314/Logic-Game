#version 450 core



layout (location = 0) in vec4 pos;	// Position of the rectangle containing the bus.
layout (location = 1) in uint type;	// Type of the current bus section.

out vec2 relative_pos;	// Position in the grid of the bus.
flat out uint bus_type;	// Type of the current bus section.

uniform vec2 offset;	// Offset of the node component if needed.
uniform mat4 viewport;	// Viewport of the grid camera.



void main() {
	gl_Position = viewport * vec4(pos.xy + offset, 0.0, 1.0);
	relative_pos = pos.zw;
	bus_type = type;
}
