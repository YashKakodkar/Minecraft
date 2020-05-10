
#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include <GLFW/glfw3.h>
#include <block.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include <vector>

struct TerrainGenerator {

public:
    void create_terrain(std::vector<glm::vec4>& block_vertices, std::vector<glm::uvec3>& block_faces);
    void sinusoidal_height();
    void perlin_noise();

private:
    std::vector<Block> blocks;
};

#endif