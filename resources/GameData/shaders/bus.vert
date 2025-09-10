#version 450 core



layout (location = 0) in vec4 pos;	// Position of the rectangle containing the bus.

out vec2 relative_pos;	// Position in the grid of the bus.

uniform mat4 viewport;



void main() {
    gl_Position = viewport * vec4(pos.xy, 0.0, 1.0);
	relative_pos = pos.zw;
}
