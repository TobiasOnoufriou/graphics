#version 330 core
//layout (location = 0) in vec3 aPos;
in vec2 pos;

void main(){
	gl_Position = vec4(pos,0.0, 1.0);
}