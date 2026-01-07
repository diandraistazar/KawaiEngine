#version 430 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoor;

out vec4 vertPosition;
out vec4 vertColor;
out vec2 vertTexCoor;

uniform mat4 matrix;

void main(){
	gl_Position = matrix * vec4(Pos, 1.0f);
	vertPosition = vec4(Pos, 1.0f);
	vertColor = vec4(Color, 1.0f);
	vertTexCoor = TexCoor;
}
