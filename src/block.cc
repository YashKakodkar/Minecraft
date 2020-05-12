#include "block.h"
#include <iostream>

namespace {
const int kMinLevel = 0;
const int kMaxLevel = 4;
};

Block::Block()
{
    // Add additional initialization if you like
}

Block::~Block()
{
}

void Block::create_block(std::vector<glm::vec4>& block_vertices, std::vector<glm::uvec3>& block_faces)
{
}

bool Block::is_dirty() const
{
    return dirty_;
}

void Block::set_clean()
{
    dirty_ = false;
}

// FIXME generate Block sponge geometry
void Block::generate_multiBlocks(std::vector<glm::vec4>& obj_vertices,
    std::vector<glm::uvec3>& obj_faces) const
{

    obj_faces.clear();
    obj_vertices.clear();
    float minx = -32;
    float miny = -32;
    float minz = -32;
    float maxx = -30.0;
    float maxy = -30.0;
    float maxz = -30.0;
    int arrayStart = 0;
    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 32; y++) {
            for (int z = 0; z < 32; z++) {
                draw_block(obj_vertices, obj_faces, minx + x * 1, miny + y * 1, minz + z * 1, maxx + x * 1, maxy + y * 1, maxz + z * 1, arrayStart);
                arrayStart += 36;
            }
        }
    }
}

void Block::generate_multiBlocksLenth(std::vector<glm::vec4>& obj_vertices,

    std::vector<glm::uvec3>& obj_faces, float startx, float starty, float startz, float length) const
{

    obj_faces.clear();
    obj_vertices.clear();
    float change = length / 2.0;
    float minx = startx;
    float miny = starty;
    float minz = startz;
    float maxx = startx + length;
    float maxy = starty + length;
    float maxz = startz + length;
    int arrayStart = 0;
    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 32; y++) {
            for (int z = 0; z < 32; z++) {
                draw_block(obj_vertices, obj_faces, minx + x * change, miny + y * change, minz + z * change, maxx + x * change, maxy + y * change, maxz + z * change, arrayStart);
                arrayStart += 36;
            }
        }
    }
}

void Block::generate_multiBlocksTextured(std::vector<glm::vec4>& obj_vertices, std::vector<glm::vec2>& texture,

    std::vector<glm::uvec3>& obj_faces, float startx, float starty, float startz, float length) const
{
    texture.clear();
    obj_faces.clear();
    obj_vertices.clear();
    float change = length / 2.0;
    float minx = startx;
    float miny = starty;
    float minz = startz;
    float maxx = startx + length;
    float maxy = starty + length;
    float maxz = startz + length;
    int arrayStart = 0;
    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 32; y++) {
            for (int z = 0; z < 32; z++) {
                draw_blockTextured(obj_vertices, obj_faces, texture, minx + x * change, miny + y * change, minz + z * change, maxx + x * change, maxy + y * change, maxz + z * change, arrayStart);
                //draw_block(obj_vertices, obj_faces, minx + x * change, miny + y * change, minz + z * change, maxx + x * change, maxy + y * change, maxz + z * change, arrayStart);
                arrayStart += 36;
            }
        }
    }
}

int Block::recursive_box(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces, float length,
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
                        draw_block(obj_vertices, obj_faces, x, y, z, x + length, y + length, z + length, arrayStart);
                        arrayStart += 36;
                    }
                }
            }
        }
    }
    return arrayStart;
}

void Block::draw_block(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces,
    float minx, float miny, float minz, float maxx, float maxy, float maxz, int arrayStart) const
{

    //front
    //bot left
    obj_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart, arrayStart + 1, arrayStart + 2));

    //top right
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, maxz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 3, arrayStart + 4, arrayStart + 5));

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

void Block::draw_blockTextured(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces, std::vector<glm::vec2>& texture,
    float minx, float miny, float minz, float maxx, float maxy, float maxz, int arrayStart) const
{

    /*
    TODO:

    There are 6 faces per block
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
    texture.push_back(glm::vec2(0.0, 0.0));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    texture.push_back(glm::vec2(1.0, 0.0));
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    texture.push_back(glm::vec2(0.0, 1.0));
    obj_faces.push_back(glm::uvec3(arrayStart, arrayStart + 1, arrayStart + 2));
    // glm::dvec3 test = getNormal(glm::dvec3(minx, miny, maxz), glm::dvec3(maxx, miny, maxz),
    //     glm::dvec3(minx, maxy, maxz));
    //std::cout << test[0] << " | " << test[1] << " | " << test[2] << std::endl;
    //top right
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    texture.push_back(glm::vec2(0.0, 1.0));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    texture.push_back(glm::vec2(1.0, 0.0));
    obj_vertices.push_back(glm::vec4(maxx, maxy, maxz, 1.0f));
    texture.push_back(glm::vec2(1.0, 1.0));
    obj_faces.push_back(glm::uvec3(arrayStart + 3, arrayStart + 4, arrayStart + 5));
    // glm::dvec3 test2 = getNormal(glm::dvec3(minx, maxy, maxz), glm::dvec3(maxx, miny, maxz),
    //     glm::dvec3(maxx, maxy, maxz));
    //std::cout << test2[0] << " | " << test2[1] << " | " << test2[2] << std::endl;
    //back-------------------------------------------------------
    //botleft

    obj_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, miny, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    texture.push_back(glm::vec2(1.0, 0.0));
    texture.push_back(glm::vec2(0.0, 0.0));
    texture.push_back(glm::vec2(0.0, 1.0));
    obj_faces.push_back(glm::uvec3(arrayStart + 6, arrayStart + 7, arrayStart + 8));

    //top right

    obj_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    texture.push_back(glm::vec2(1.0, 0.0));
    texture.push_back(glm::vec2(0.0, 1.0));
    texture.push_back(glm::vec2(1.0, 1.0));
    obj_faces.push_back(glm::uvec3(arrayStart + 9, arrayStart + 10, arrayStart + 11));

    //top---------------------------------------------------------
    //botleft

    obj_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    texture.push_back(glm::vec2(0.0, 0.0));
    texture.push_back(glm::vec2(0.0, 1.0));
    texture.push_back(glm::vec2(1.0, 0.0));
    obj_faces.push_back(glm::uvec3(arrayStart + 12, arrayStart + 13, arrayStart + 14));

    //top right
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    texture.push_back(glm::vec2(0.0, 1.0));
    texture.push_back(glm::vec2(1.0, 1.0));
    texture.push_back(glm::vec2(1.0, 0.0));
    obj_faces.push_back(glm::uvec3(arrayStart + 15, arrayStart + 16, arrayStart + 17));

    //bottom--------------------------------------------------------
    //botleft
    obj_vertices.push_back(glm::vec4(minx, miny, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    obj_faces.push_back(glm::uvec3(arrayStart + 18, arrayStart + 19, arrayStart + 20));
    texture.push_back(glm::vec2(0.0, 0.0));
    texture.push_back(glm::vec2(0.0, 1.0));
    texture.push_back(glm::vec2(1.0, 0.0));
    //top right
    obj_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    texture.push_back(glm::vec2(0.0, 1.0));
    texture.push_back(glm::vec2(1.0, 1.0));
    texture.push_back(glm::vec2(1.0, 0.0));
    obj_faces.push_back(glm::uvec3(arrayStart + 21, arrayStart + 22, arrayStart + 23));

    //right--------------------------------------------------------
    //botleft
    obj_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, minz, 1.0f));
    texture.push_back(glm::vec2(1.0, 0.0));
    texture.push_back(glm::vec2(0.0, 1.0));
    texture.push_back(glm::vec2(0.0, 0.0));
    obj_faces.push_back(glm::uvec3(arrayStart + 24, arrayStart + 25, arrayStart + 26));

    //top right

    obj_vertices.push_back(glm::vec4(maxx, maxy, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(maxx, maxy, minz, 1.0f));
    texture.push_back(glm::vec2(1.0, 1.0));
    texture.push_back(glm::vec2(0.0, 1.0));
    texture.push_back(glm::vec2(1.0, 0.0));
    obj_faces.push_back(glm::uvec3(arrayStart + 27, arrayStart + 28, arrayStart + 29));

    //left--------------------------------------------------------
    //botleft
    obj_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, miny, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    texture.push_back(glm::vec2(1.0, 0.0));
    texture.push_back(glm::vec2(0.0, 0.0));
    texture.push_back(glm::vec2(0.0, 1.0));
    obj_faces.push_back(glm::uvec3(arrayStart + 30, arrayStart + 31, arrayStart + 32));

    //top right
    obj_vertices.push_back(glm::vec4(minx, maxy, minz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, miny, maxz, 1.0f));
    obj_vertices.push_back(glm::vec4(minx, maxy, maxz, 1.0f));
    texture.push_back(glm::vec2(1.0, 0.0));
    texture.push_back(glm::vec2(0.0, 1.0));
    texture.push_back(glm::vec2(1.0, 1.0));
    obj_faces.push_back(glm::uvec3(arrayStart + 33, arrayStart + 34, arrayStart + 35));
}
