#version 430 core
in vec4 vertPosition;
in vec4 vertColor;
in vec2 vertTexCoor;

out vec4 fragColor;

uniform sampler2D uTexture;

void main(){
	fragColor = texture(uTexture, vertTexCoor);
}
