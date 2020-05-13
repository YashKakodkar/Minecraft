R"zzz(#version 330 core
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform vec4 light_position;
uniform vec3 chunk_pos[512];


uniform vec3 camera_position;
in vec4 vertex_position;
in vec4 normal;
in vec2 uv;
in vec3 color;
out vec4 vs_light_direction;
out vec4 vs_normal;
out vec2 vs_uv;
out vec4 vs_camera_direction;
out vec3 coloring;
layout(location = 1) in vec3 vertexColor;
in vec2 texture_uv;
out vec2 texture_uv_pass;
void main() {
	mat4 mvp = projection * view * model;
	vec4 position = vec4(vertex_position.xyz, 1.0);
	gl_Position = mvp * position;

	vs_light_direction = light_position - gl_Position;
	vs_camera_direction = vec4(camera_position, 1.0) - gl_Position;
	vs_normal = normal;
	vs_uv = uv;
	coloring = vertexColor;
	texture_uv_pass = texture_uv;
})zzz"