R"zzz(
#version 330 core
out vec4 fragment_color;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
   fragment_color  = texture(skybox, TexCoords);
}
)zzz"