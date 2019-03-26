#version 330 core

layout(points) in;
layout(line_strip, max_vertices = 5 ) out;
const float PI = 3.1415926;

out vec3 fColor;
uniform float u_time;
void build_wave(vec4 position){

    fColor = gs_in[0].color;
    gl_Position = position + vec4(0.2, 0.2, 0.3, 0.0);    // 1:bottom-left
    EmitVertex();   
    gl_Position = position + vec4( 0.2, 0.2, 0.0, 0.0);    // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:top-left
    EmitVertex();
    gl_Position = position + vec4( -0.2,  -0.2, 0.0, 0.0);    // 4:top-right
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:top
    EmitVertex();
    //fColor = vec3(1.0,1.0,1.0);
    EndPrimitive();
}
void main(){

      /*for (int i = 0; i <= 10; i++) {
        // Angle between each side in radians
        float ang = PI * 2.0 / 10.0 * i;
        // Offset from center of point (0.3 to accomodate for aspect ratio)
        vec4 offset = vec4(cos(ang) * 0.3, -sin(ang) * 0.3, 1.0, 0.0);
        gl_Position = gl_in[0].gl_Position + offset;
        EmitVertex();
    }*/
    build_wave(gl_in[0].gl_Position);
}