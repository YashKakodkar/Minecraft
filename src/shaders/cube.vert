R"zzz(#version 330 core
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform vec4 light_position;
uniform vec3 chunk_pos[512];
in vec4 vertex_position;
in vec2 texture_uv;
out vec2 texture_uv_pass;
void main() {
	mat4 mvp = projection * view * model;
	vec4 position = vec4(vertex_position.xyz + chunk_pos[gl_InstanceID], 1.0);
	gl_Position = mvp * position;
	texture_uv_pass = texture_uv;
})zzz"