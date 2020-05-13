#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"
#include "config.h"
#include "perlin.h"
#include <glm/glm.hpp>
#include <vector>

class Chunk {
public:
    Chunk(int x, int z);

    Chunk(const Chunk&) = delete;
    Chunk& operator=(const Chunk&) = delete;

    Chunk() = default;
    ~Chunk() = default; /// Protected non-virtual destructor
    void create_mesh(int x_grid, int y_grid, int z_grid);
    void create_mesh(int x_grid, int z_grid);
    void create_blockC(float x_start, float y_start, float z_start, float size, int arrayStart);
    static const int CHUNK_SIZE = 16;
    std::vector<glm::vec4> block_vertices;
    std::vector<glm::vec3> block_color;
    std::vector<glm::uvec3> block_faces;
    std::vector<glm::vec3> block_positions;
    bool ye = false;
    Perlin perlin;
    Block*** blocks;
    int x_length;
    int z_length;
};

#endif