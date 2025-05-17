#version 450 core
layout(location = 0) in uint inv;
uniform uint ofs;
out uint outv;
void main(){
	outv = inv + ofs;
}
