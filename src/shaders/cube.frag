R"zzz(
#version 330 core
in vec4 face_normal;
in vec4 vertex_normal;
in vec4 light_direction;
in vec4 world_position;
out vec4 fragment_color;
uniform sampler2D myTextureSampler;

void main() {
  fragment_color = vec4(0.0, 1.0, 0.0, 1.0);
}
)zzz"