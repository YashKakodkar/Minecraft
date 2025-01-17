#ifndef PROCEDURE_GEOMETRY_H
#define PROCEDURE_GEOMETRY_H

#include <glm/glm.hpp>
#include <vector>

//struct LineMesh;

void create_floor(std::vector<glm::vec4>& floor_vertices, std::vector<glm::uvec3>& floor_faces);
void create_cube(std::vector<glm::vec4>& cube_vertices, std::vector<glm::uvec3>& cube_faces);
glm::dvec3 getNormal(glm::dvec3 x, glm::dvec3 y, glm::dvec3 z);
// void create_bone_mesh(LineMesh& bone_mesh);
// void create_cylinder_mesh(LineMesh& cylinder_mesh);
// void create_axes_mesh(LineMesh& axes_mesh);

#endif
