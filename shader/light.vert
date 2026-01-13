#version 430 core

in vec3 pos;

uniform mat4 model;
uniform mat4 matrix;

void main(){
	gl_Position = matrix * model * vec4(pos, 1.0f);
}
