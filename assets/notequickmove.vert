#version 450 core
layout(location = 0) in vec2 pos;
uniform vec2 quickmovepos;
uniform vec2 iconpos;
uniform vec2 windowsize;
out vec2 txpos;
void main(){
	gl_Position = vec4(2.0 * ((1.5 * pos.x + iconpos.x + quickmovepos.x) / windowsize.x - 0.5), -2.0 * ((1.5 * pos.y + iconpos.y + quickmovepos.y) / windowsize.y - 0.5), 0.0, 1.0);
	txpos = vec2(pos.x, pos.y);
}
