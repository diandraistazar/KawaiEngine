#version 430 core
in vec3 fragPosition;
in vec3 fragColor;
in vec2 fragTexCoor;
in vec3 fragNormal;

out vec4 outColor;

uniform sampler2D uTexture;
uniform struct{
	vec3 position;
	vec3 color;
	float radius;
	float ambient;
} light;

void main(){
	vec4 texture_color = texture(uTexture, fragTexCoor);
	vec4 light_color = vec4(light.color, 1.0f);

	// Ambient
	vec4 ambient = texture_color * light.ambient;

	// Diffuse light
	vec3 light_direction = light.position - fragPosition;
	float light_length = length(light_direction);
	float light_radius = (light.radius - light_length) * 0.5f;
	float brightness = dot(fragNormal, normalize(light_direction)) + light_radius;
	brightness = max(brightness, 0.0f);

	// Specular

	// Store into the current fragment
	outColor = texture_color * light_color * brightness + ambient;
}
