R"zzz(#version 330 core
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform vec4 light_position;
in vec4 vertex_position;
void main() {
	mat4 mvp = projection * view * model;
	vec4 position = vertex_position;
	gl_Position = mvp * position;
})zzz"