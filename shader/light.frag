#version 430 core

out vec4 outColor;

uniform struct Light{
	vec3 lighting;
} light;

void main(){
	outColor = vec4(light.lighting, 1.0f);
}
