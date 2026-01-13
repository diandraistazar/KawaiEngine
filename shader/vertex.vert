#version 430 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoor;
layout (location = 3) in vec3 Normal;

out vec3 fragPosition;
out vec3 fragColor;
out vec2 fragTexCoor;
out vec3 fragNormal;

uniform mat4 model; // only model matrix
uniform mat4 matrix; // contains view and projection matrix
uniform mat3 normal_matrix; // a matrix for normal vector
uniform struct Light{
	vec3 position;
	vec3 lighting;
} light;

void main(){
	fragPosition = vec3(model * vec4(Pos, 1.0f));
	fragColor = Color;
	fragTexCoor = TexCoor;
	fragNormal = normalize(normal_matrix * Normal); // Normal vector in world space
	gl_Position = matrix * model * vec4(Pos, 1.0f);
}
