#version 430 core
layout (location = 0) in vec3 verPos;

void main(){
	gl_Position = vec4(verPos, 1.0f);
}
