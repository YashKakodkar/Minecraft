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
