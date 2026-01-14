#version 430 core

out vec4 outColor;

uniform struct{
	vec3 color;
} light;

void main(){
	outColor = vec4(light.color, 1.0f);
}
