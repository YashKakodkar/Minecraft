R"zzz(
#version 330 core
in vec4 face_normal;
in vec4 vertex_normal;
in vec4 light_direction;
in vec4 world_position;
out vec4 fragment_color;
in vec2 texture_uv_pass;
uniform sampler2D myTextureSampler;

void main() {
  fragment_color = vec4(0.0, 1.0, 0.0, 1.0);
  //fragment_color = texture(myTextureSampler, texture_uv_pass);
}
)zzz"