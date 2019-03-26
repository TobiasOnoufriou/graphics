#version 330 core
out vec4 fragColor;

uniform vec4 newColor;


void main(){
	fragColor = vec4 (newColor.x, newColor.y, newColor.z, 1.0f);
}