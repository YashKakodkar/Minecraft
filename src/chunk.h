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
    ~Chunk();

    void create_mesh(int x_grid, int y_grid, int z_grid);
    void update(float dt);
    void create_mesh(int x_grid, int z_grid);
    void generate_plane(int x, int z);
    void create_block();
    void create_block(float x_start, float y_start, float z_start, float size, int array_start);
    void create_block(int size);
    static const int CHUNK_SIZE = 16;
    std::vector<glm::vec4> block_vertices;
    std::vector<glm::uvec3> block_faces;
    std::vector<glm::vec3> block_positions;

private:
    Perlin perlin;
    Block*** blocks;
    int x_length;
    int z_length;
};

#endif