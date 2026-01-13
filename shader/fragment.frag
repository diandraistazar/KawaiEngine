#version 430 core
in vec3 fragPosition;
in vec3 fragColor;
in vec2 fragTexCoor;
in vec3 fragNormal;

out vec4 outColor;

uniform sampler2D uTexture;
uniform struct Light{
	vec3 position;
	vec3 lighting;
} light;

void main(){
	// Diffuse light
	vec3 light_direction = normalize(light.position - fragPosition);
	float brightness = dot(fragNormal, light_direction);

	if(brightness <= 0.0f)
		return;

	vec4 texture_color = texture(uTexture, fragTexCoor);
	vec4 lighting = vec4(light.lighting, 1.0f);
	// Store into the current fragment
	outColor = texture_color * lighting * brightness;
}
