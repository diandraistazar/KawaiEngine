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
	float specular;
} light;

uniform struct{
	vec3 position;
} view;

vec3 reflect_vec3(vec3 normal, vec3 vector){
	return vector - (2 * (dot(normal, vector)) * normal);
}

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
	vec3 reflected_direction = reflect_vec3(fragNormal, normalize(light_direction) * -1.0f);
	vec3 view_direction = normalize(view.position - fragPosition);
	float specular = dot(reflected_direction, view_direction);
	specular = max(pow(specular, 42), 0.0f) * light.specular;

	// Store into the current fragment
	outColor = texture_color * light_color * brightness + specular + ambient;
}
