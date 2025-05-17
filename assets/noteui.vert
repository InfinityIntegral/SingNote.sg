#version 450 core
layout(location = 0) in vec2 pos;
uniform vec3 viewportdata;
uniform vec2 windowsize;
uniform uint incolour;
uniform vec2 poscenter;
uniform int rendertype;
uniform vec2 selectortopleft;
uniform vec2 selectorsize;
uniform float sizeunit;
out vec4 outcolour;
out vec2 localcoords;
out vec2 txpos;
void main(){
	outcolour = vec4(float(uint(0xFF) & (incolour >> 24)) / 255.0, float(uint(0xFF) & (incolour >> 16)) / 255.0, float(uint(0xFF) & (incolour >> 8)) / 255.0, 0.5);
	if(rendertype == 0){
		gl_Position = vec4(2.0 * (poscenter.x + pos.x - viewportdata.x) / viewportdata.z, 2.0 * (poscenter.y + pos.y - viewportdata.y) / viewportdata.z * windowsize.x / windowsize.y, 0.0, 1.0);
		localcoords = vec2(pos.x, pos.y) / abs(pos.x);
	}
	else if(rendertype == 1){
		gl_Position = vec4(2.0 * (selectortopleft.x + selectorsize.x * pos.x - viewportdata.x) / viewportdata.z, 2.0 * (selectortopleft.y + selectorsize.y * pos.y - viewportdata.y) / viewportdata.z * windowsize.x / windowsize.y, 0.0, 1.0);
		localcoords = vec2(0.0, 0.0);
	}
	else if(rendertype == 2){
		gl_Position = vec4(2.0 * (selectortopleft.x + selectorsize.x - viewportdata.x) / viewportdata.z + 2.0 * 1.5 * (pos.x - 0.5) / windowsize.x * sizeunit, 2.0 * (selectortopleft.y - viewportdata.y) / viewportdata.z * windowsize.x / windowsize.y + 2.0 * 1.5 * (pos.y - 0.5) / windowsize.y * sizeunit, 0.0, 1.0);
		localcoords = vec2(20.0, 0.0);
		txpos = vec2(pos.x, pos.y);
	}
}
