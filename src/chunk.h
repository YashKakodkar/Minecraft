#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"
#include "config.h"
#include <glm/glm.hpp>
#include <vector>

class Chunk {
public:
    Chunk();
    ~Chunk();

    void update(float dt);
    void create_mesh();
    void create_block();
    void create_block(std::vector<glm::vec4>& block_vertices, std::vector<glm::uvec3>& block_faces, int size);
    static const int CHUNK_SIZE = 16;

private:
    Block*** blocks;
};

#endif