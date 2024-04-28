#version 330

out vec4 final_color;
#define RADIUS 500

uniform vec2 screen_center;

void main() {
	vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);
	float d = 0;
	d = distance(pos, screen_center) / screen_center;

}
