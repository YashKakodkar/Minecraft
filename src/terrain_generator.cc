#include "terrain_generator.h"
#include "config.h"
#include "texture_to_render.h"
#include <fstream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <queue>
#include <stdexcept>

void Block::create_block(std::vector<glm::vec4>& block_vertices, std::vector<glm::uvec3>& block_faces)
{
}

void TerrainGenerator::create_terrain(std::vector<glm::vec4>& block_vertices, std::vector<glm::uvec3>& block_faces)
{
}

void TerrainGenerator::sinusoidal_height()
{
}

void TerrainGenerator::perlin_noise()
{
}
