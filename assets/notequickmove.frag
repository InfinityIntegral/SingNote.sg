#version 450 core
in vec2 txpos;
uniform sampler2D icontexture;
uniform uint colour1;
uniform uint colour2;
out vec4 fcolour;
void main(){
	vec4 c1 = vec4(float(uint(0xFF) & (colour1 >> 24)) / 255.0, float(uint(0xFF) & (colour1 >> 16)) / 255.0, float(uint(0xFF) & (colour1 >> 8)) / 255.0, 1.0);
	vec4 c2 = vec4(float(uint(0xFF) & (colour2 >> 24)) / 255.0, float(uint(0xFF) & (colour2 >> 16)) / 255.0, float(uint(0xFF) & (colour2 >> 8)) / 255.0, 1.0);
	vec4 isshaded = texture(icontexture, txpos);
	if(isshaded.a > 0.5){fcolour = c2;}
	else{fcolour = c1;}
}
