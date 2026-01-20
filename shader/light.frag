#version 430 core

out vec4 outColor;

uniform struct{
	vec3 color;
	vec3 intensity;
} light;

void main(){
	outColor = vec4(light.color * light.intensity, 1.0f);
}
