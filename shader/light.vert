#version 430 core

in vec3 pos;

uniform struct {
	mat4 model;
	mat4 eye;
}matrix;

void main(){
	gl_Position = matrix.eye * matrix.model * vec4(pos, 1.0f);
}
