#version 450 core
layout(location = 0) in vec2 pos;
uniform vec3 viewportdata;
uniform vec2 windowsize;
void main(){
	gl_Position = vec4(2.0 * (pos.x - viewportdata.x) / viewportdata.z, 2.0 * (pos.y - viewportdata.y) / viewportdata.z * windowsize.x / windowsize.y, 0.0, 1.0);
}
