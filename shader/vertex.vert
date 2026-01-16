#version 430 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoor;
layout (location = 3) in vec3 Normal;

out vec3 fragPosition;
out vec3 fragColor;
out vec2 fragTexCoor;
out vec3 fragNormal;

uniform struct{
	mat4 model;
	mat4 eye;
	mat3 normal;
} matrix;

void main(){
	fragPosition = vec3(matrix.model * vec4(Pos, 1.0f));
	fragColor = Color;
	fragTexCoor = TexCoor * 3.0f;
	fragNormal = normalize(matrix.normal * Normal); // Normal vector in world space
	gl_Position = matrix.eye * matrix.model * vec4(Pos, 1.0f);
}
