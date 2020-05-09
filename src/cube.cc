#include "cube.h"
#include <iostream>

namespace {
const int kMinLevel = 0;
const int kMaxLevel = 4;
};

Cube::Cube()
{
    // Add additional initialization if you like
}

Cube::~Cube()
{
}

void Cube::set_nesting_level(int level)
{
    nesting_level_ = level;
    dirty_ = true;
}

bool Cube::is_dirty() const
{
    return dirty_;
}

void Cube::set_clean()
{
    dirty_ = false;
}

// FIXME generate Cube sponge geometry
void Cube::generate_geometry(std::vector<glm::vec4>& obj_vertices,
    std::vector<glm::uvec3>& obj_faces) const
{

    obj_faces.clear();
    obj_vertices.clear();
    float minx = -.5;
    float miny = -.5;
    float minz = -0.5;
    float maxx = .5;
    float maxy = .5;
    float maxz = 0.5;
    if (nesting_level_ != 0) {
        //draw_cube(obj_vertices, obj_faces, 0, minx, miny, minz, maxx,maxy, maxz);
        // std::cout << length/3.0 << std::endl;
        recursive_box(obj_vertices, obj_faces, 1 / 3.0, minx, miny, minz, nesting_level_, 0);
    } else {
        draw_cube(obj_vertices, obj_faces, minx, miny, minz, maxx, maxy, maxz, 0);
    }
}

int Cube::recursive_box(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces, float length,
    float minx, float miny, float minz, int level, int arrayStart) const
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                bool isMiddle = (i == 1 && j == 1) || (i == 1 && k == 1)
                    || (j == 1 && k == 1);
                if (!isMiddle) {
                    float x = minx + i * length;
                    float y = miny + j * length;
                    float z = minz + k * length;
                    //std::cout << length << "\n";
                    // std::cout << minx << " | " << miny << " | " << " | " << minz << std::endl;
                    //std::cout << level << "\n";
                    if (level > 1) {
                        //                        std::cout << x << " | " << y << " | " << " | " << z << std::endl;
                        //std::cout << level<< "\n";
                        arrayStart = recursive_box(obj_vertices, obj_faces, length / 3.0, x, y, z, level - 1,
                            arrayStart);
                    } else {
                        //std::cout << "hi";
                        draw_cube(obj_vertices, obj_faces, x, y, z, x + length, y + length, z + length, arrayStart);
                        arrayStart += 36;
                    }
                }
            }
        }
    }
    return arrayStart;
}

// glm::dvec3 getNormal(glm::dvec3 x, glm::dvec3 y, glm::dvec3 z)
// {
//     glm::dvec3 ab = y - x;
//     glm::dvec3 ac = z - x;
//     glm::dvec3 normal = glm::normalize(glm::cross(ab, ac));
//     return normal;
// }

void Cube::draw_cube(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces,
    float minx, float miny, float minz, float maxx, float maxy, float maxz, int arrayStart) const
{

    /*
    TODO:

    There are 6 faces per cube
    Each face can be drawn by 2 triangles each on opposite corners

    Draw both triangles per face.


    */
    //    obj_vertices.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));
    //    obj_vertices.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f));
    //    obj_vertices.push_back(glm::vec4(0.0f, 0.5f, -0.5f, 1.0f));
    //    obj_faces.push_back(glm::uvec3(0, 1, 2));
    //    std::cout << minx << " " << miny << " " << minz << std::endl;
    //    std::cout << maxx << " " << maxy << " " << maxz << std::endl;
    //front
    //bot left
    //std::cout << minx << " | " << miny << " | " << " | " << minz << std::endl;
    obj_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart, arrayStart + 1, arrayStart + 2));
    // glm::dvec3 test = getNormal(glm::dvec3(minx, miny, maxz), glm::dvec3(maxx, miny, maxz),
    //     glm::dvec3(minx, maxy, maxz));
    //std::cout << test[0] << " | " << test[1] << " | " << test[2] << std::endl;
    //top right
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, maxz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 3, arrayStart + 4, arrayStart + 5));
    // glm::dvec3 test2 = getNormal(glm::dvec3(minx, maxy, maxz), glm::dvec3(maxx, miny, maxz),
    //     glm::dvec3(maxx, maxy, maxz));
    //std::cout << test2[0] << " | " << test2[1] << " | " << test2[2] << std::endl;
    //back-------------------------------------------------------
    //botleft

    obj_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, miny, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 6, arrayStart + 7, arrayStart + 8));

    //top right

    obj_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 9, arrayStart + 10, arrayStart + 11));

    //top---------------------------------------------------------
    //botleft

    obj_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 12, arrayStart + 13, arrayStart + 14));

    //top right
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 15, arrayStart + 16, arrayStart + 17));

    //bottom--------------------------------------------------------
    //botleft
    obj_vertices.push_back(glm::vec4(minx, miny, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 18, arrayStart + 19, arrayStart + 20));

    //top right
    obj_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 21, arrayStart + 22, arrayStart + 23));

    //right--------------------------------------------------------
    //botleft
    obj_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 24, arrayStart + 25, arrayStart + 26));

    //top right

    obj_vertices.push_back(glm::vec4(maxx, maxy, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 27, arrayStart + 28, arrayStart + 29));

    //left--------------------------------------------------------
    //botleft
    obj_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, miny, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 30, arrayStart + 31, arrayStart + 32));

    //top right
    obj_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 33, arrayStart + 34, arrayStart + 35));
}
