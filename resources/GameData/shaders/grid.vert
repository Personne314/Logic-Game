#version 450 core

layout (location = 0) in vec2 pos;	// Position of the rectangle containing the grid.

uniform mat4 inv_viewport;	// Inverse of the viewport camera.

out vec2 grid_pos;	// Pos equivalent in the grid coordinate system.

void main()
{
	gl_Position = vec4(pos, 0.0, 1.0);
	grid_pos = (inv_viewport * vec4(pos, 0.0, 1.0)).xy;
}
