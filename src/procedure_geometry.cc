#include "procedure_geometry.h"
#include "config.h"
#include <glm/glm.hpp>

void create_floor(std::vector<glm::vec4>& floor_vertices, std::vector<glm::uvec3>& floor_faces)
{
    floor_vertices.push_back(glm::vec4(kFloorXMin, kFloorY, kFloorZMax, 1.0f));
    floor_vertices.push_back(glm::vec4(kFloorXMax, kFloorY, kFloorZMax, 1.0f));
    floor_vertices.push_back(glm::vec4(kFloorXMax, kFloorY, kFloorZMin, 1.0f));
    floor_vertices.push_back(glm::vec4(kFloorXMin, kFloorY, kFloorZMin, 1.0f));
    floor_faces.push_back(glm::uvec3(0, 1, 2));
    floor_faces.push_back(glm::uvec3(2, 3, 0));
}

glm::dvec3 getNormal(glm::dvec3 x, glm::dvec3 y, glm::dvec3 z)
{
    glm::dvec3 ab = y - x;
    glm::dvec3 ac = z - x;
    glm::dvec3 normal = glm::normalize(glm::cross(ab, ac));
    return normal;
}

void create_cube(std::vector<glm::vec4>& cube_vertices, std::vector<glm::uvec3>& cube_faces)
{
    float minx = -.5;
    float miny = -.5;
    float minz = -0.5;
    float maxx = .5;
    float maxy = .5;
    float maxz = 0.5;
    int arrayStart = 0;
    /*
    TODO:

    There are 6 faces per cube
    Each face can be drawn by 2 triangles each on opposite corners

    Draw both triangles per face.


    */
    //    cube_vertices.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
    //    cube_vertices.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
    //    cube_vertices.push_back(glm::vec4(0.0f, 0.5f, -0.5f, 1.0f));
    //    cube_faces.push_back(glm::uvec3(0, 1, 2));
    //    std::cout << minx << " " << miny << " " << minz << std::endl;
    //    std::cout << maxx << " " << maxy << " " << maxz << std::endl;
    //front
    //bot left
    //std::cout << minx << " | " << miny << " | " << " | " << minz << std::endl;
    cube_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart, arrayStart + 1, arrayStart + 2));
    glm::dvec3 test = getNormal(glm::dvec3(minx, miny, maxz), glm::dvec3(maxx, miny, maxz),
        glm::dvec3(minx, maxy, maxz));
    //std::cout << test[0] << " | " << test[1] << " | " << test[2] << std::endl;
    //top right
    cube_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, maxy, maxz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 3, arrayStart + 4, arrayStart + 5));
    glm::dvec3 test2 = getNormal(glm::dvec3(minx, maxy, maxz), glm::dvec3(maxx, miny, maxz),
        glm::dvec3(maxx, maxy, maxz));
    //std::cout << test2[0] << " | " << test2[1] << " | " << test2[2] << std::endl;
    //back-------------------------------------------------------
    //botleft

    cube_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    cube_vertices.push_back(glm::vec4(minx, miny, minz, 1.0f));
    cube_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 6, arrayStart + 7, arrayStart + 8));

    //top right

    cube_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    cube_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 9, arrayStart + 10, arrayStart + 11));

    //top---------------------------------------------------------
    //botleft

    cube_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    cube_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 12, arrayStart + 13, arrayStart + 14));

    //top right
    cube_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, maxy, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 15, arrayStart + 16, arrayStart + 17));

    //bottom--------------------------------------------------------
    //botleft
    cube_vertices.push_back(glm::vec4(minx, miny, minz, 1.0f));
    cube_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 18, arrayStart + 19, arrayStart + 20));

    //top right
    cube_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 21, arrayStart + 22, arrayStart + 23));

    //right--------------------------------------------------------
    //botleft
    cube_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 24, arrayStart + 25, arrayStart + 26));

    //top right

    cube_vertices.push_back(glm::vec4(maxx, maxy, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 27, arrayStart + 28, arrayStart + 29));

    //left--------------------------------------------------------
    //botleft
    cube_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    cube_vertices.push_back(glm::vec4(minx, miny, minz, 1.0f));
    cube_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 30, arrayStart + 31, arrayStart + 32));

    //top right
    cube_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    cube_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    cube_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    cube_faces.push_back(glm::uvec3(arrayStart + 33, arrayStart + 34, arrayStart + 35));
}

// void create_bone_mesh(LineMesh& bone_mesh)
// {
// 	bone_mesh.vertices.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
// 	bone_mesh.vertices.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
// 	bone_mesh.indices.push_back(glm::uvec2(0, 1));
// }

/*
 * Create Cylinder from x = -0.5 to x = 0.5
 */
// void create_cylinder_mesh(LineMesh& cylinder_mesh)
// {
//     constexpr int kCylinderGridSizeX = 16; // number of points in each direction
//     constexpr int kCylinderGridSizeY = 3; // number of points in each direction
//     float step_x = 1.0f / (kCylinderGridSizeX - 1);
//     float step_y = 1.0f / (kCylinderGridSizeY - 1);
//     glm::vec3 p = glm::vec3(-0.5f, 0.0f, 0.0f);

//     // Setup the vertices of the lattice.
//     // Note: vertex shader is used to generate the actual cylinder
//     // Extra Credit: Optionally you can use tessellation shader to draw the
//     //               cylinder
//     for (int i = 0; i < kCylinderGridSizeY; ++i) {
//         p.x = -0.5f;
//         for (int j = 0; j < kCylinderGridSizeX; ++j) {
//             cylinder_mesh.vertices.push_back(glm::vec4(p, 1.0f));
//             p.x += step_x;
//         }
//         p.y += step_y;
//     }

//     // Compute the indices, this is just column / row indexing for the
//     // vertical line segments and linear indexing for the horizontal
//     // line segments.
//     for (int n = 0; n < kCylinderGridSizeX * kCylinderGridSizeY; ++n) {
//         int row = n / kCylinderGridSizeX;
//         int col = n % kCylinderGridSizeX;
//         if (col > 0) {
//             cylinder_mesh.indices.emplace_back(n - 1, n);
//         }
//         if (row > 0) {
//             cylinder_mesh.indices.emplace_back((row - 1) * kCylinderGridSizeX + col, n);
//         }
//     }
// }

// void create_axes_mesh(LineMesh& axes_mesh)
// {
//     axes_mesh.vertices.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
//     axes_mesh.vertices.push_back(glm::vec4(2.0f, 0.0f, 0.0f, 1.0f));
//     axes_mesh.vertices.push_back(glm::vec4(0.0f, 0.0f, 2.0f, 1.0f));
//     axes_mesh.indices.push_back(glm::uvec2(0, 1));
//     axes_mesh.indices.push_back(glm::uvec2(0, 2));
// }
