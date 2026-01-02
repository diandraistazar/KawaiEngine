#version 430 core
layout (location = 0) in vec3 verPos;

uniform mat4 matrix;

void main(){
	gl_Position = matrix * vec4(verPos, 1.0f);
}
