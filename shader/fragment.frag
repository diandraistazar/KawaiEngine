#version 430 core
in vec3 fragPosition;
in vec3 fragColor;
in vec2 fragTexCoor;
in vec3 fragNormal;

out vec4 outColor;

uniform struct{
	vec3 position;
	vec3 color;
	vec3 intensity;
	vec3 ambient;
	vec3 specular;
} light;

uniform struct{
	vec3 ambient;
	vec3 specular;
} material;

uniform struct{
	vec3 position;
} view;
uniform sampler2D uTexture;

void main(){
	vec4 texture_color = texture(uTexture, fragTexCoor);

	// Ambient
	vec3 ambient = texture_color.rgb * light.ambient * material.ambient;

	// Diffuse light
	vec3 light_direction = normalize(light.position - fragPosition);
	float diffuse = max(dot(fragNormal, light_direction), 0.0f);

	// Specular
	vec3 view_direction = normalize(view.position - fragPosition);
	vec3 reflected_direction = reflect(light_direction * -1.0f, fragNormal);
	vec3 specular = light.specular * material.specular * max(pow(dot(reflected_direction, view_direction), 32), 0.0f);

	// Store into the current fragment
	outColor = texture_color * vec4(light.color * diffuse * light.intensity, 1.0f) + vec4((specular + ambient) * light.intensity, 1.0f);
}
