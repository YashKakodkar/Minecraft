R"zzz(
#version 330 core
in vec4 face_normal;
in vec4 vertex_normal;
in vec4 light_direction;
in vec4 world_position;
in vec4 camera_direction;
out vec4 fragment_color;
in vec2 texture_uv_pass;
uniform sampler2D myTextureSampler;
in vec3 coloring;
void main() {
	vec4 diffuse = vec4(0.0, 1.0, 0.0, 0.0);
	vec4 ambient = vec4(0.5, 0, 0.5, 0.0);
	vec4 specular = vec4(0.2, 0.2, 0.2, 0.0);
	float shininess = 0.5;

	vec3 color = vec3(diffuse);
	//float dot_nl = dot(normalize(light_direction), normalize(vertex_normal));
	//dot_nl = clamp(dot_nl, 0.0, 1.0);
//vec4 spec = specular * pow(max(0.0, dot(reflect(-light_direction, vertex_normal), camera_direction)), shininess);
	//color = clamp(dot_nl * color + vec3(ambient), 0.0, 1.0);
	fragment_color = vec4(color, 1.0);\

//This does not work currently
	// fragment_color = vec4(coloring, 1.0); 


  //fragment_color = texture(myTextureSampler, texture_uv_pass);
}
)zzz"