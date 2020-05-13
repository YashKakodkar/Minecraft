R"zzz(
#version 330 core
layout (location = 0) in vec3 vert;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
    TexCoords = vert;
    mat4 vp = projection * view;
    gl_Position = vp * vec4(vert, 1.0);
}  
)zzz"