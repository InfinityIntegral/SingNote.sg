#version 450 core
layout(location = 0) in vec2 pos;
uniform vec3 viewportdata;
uniform vec2 windowsize;
uniform uint incolour;
uniform int zdepth;
out vec4 outcolour;
void main(){
	gl_Position = vec4(2.0 * (pos.x - viewportdata.x) / viewportdata.z, 2.0 * (pos.y - viewportdata.y) / viewportdata.z * windowsize.x / windowsize.y, 1.0 - 0.0001 * float(zdepth), 1.0);
	outcolour = vec4(float(uint(0xFF) & (incolour >> 24)) / 255.0, float(uint(0xFF) & (incolour >> 16)) / 255.0, float(uint(0xFF) & (incolour >> 8)) / 255.0, float(uint(0xFF) & incolour) / 255.0);
}
