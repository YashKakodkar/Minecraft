#include "chunk.h"
#include "block.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <math.h>
#include <thread>
#include <vector>

Chunk::Chunk(int x, int z)
    : x_length(x)
    , z_length(z)
{
    // Create the blocks
    blocks = new Block**[CHUNK_SIZE];
    for (int i = 0; i < CHUNK_SIZE; i++) {
        blocks[i] = new Block*[CHUNK_SIZE];

        for (int j = 0; j < CHUNK_SIZE; j++) {
            blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
    std::srand(std::time(nullptr));

    create_mesh(x_length, -CHUNK_SIZE, z_length);
}

void Chunk::create_mesh(int x_grid, int y_grid, int z_grid)
{
    int arrayStart = 0;
    int i = 0;
    int high = 10;
    int low = 6;
    int prevHeight = 8;
    perlin.create_height_map(x_grid, z_grid);

    for (int x = 0; x < 16; ++x) {
        for (int z = 0; z < 16; ++z) {
            create_blockC(x_grid + x, -16, z_grid + z, 1, arrayStart);
            int height = perlin.height_map_[x][z];
            arrayStart += 36;

            for (int y = 1; y < height; ++y) {

                create_blockC(x_grid + x, y_grid + y, z_grid + z, 1, arrayStart);
                arrayStart += 36;
                if (y == height - 1 && height > 6) {
                    //std::cout << y << "  ";
                    create_blockC(x_grid + x, y_grid + 36, z_grid + z, 1, arrayStart);
                    arrayStart += 36;
                }
                i++;
            }
        }
        std::cout << std::endl;
    }
}

void Chunk::create_blockC(float x_start, float y_start, float z_start, float size, int arrayStart)
{
    int height = y_start + 16;
    glm::vec3 rgb = glm::vec3(1.0, 1.0, 1.0);
    if (height >= 0 && height < 1) {
        rgb = glm::vec3(177.0 / 255.0, 105.0 / 255.0, 50.0 / 255.0);
    } else if (height >= 1 && height < 2) {
        rgb = glm::vec3(177.0 / 255.0, 105.0 / 255.0, 50.0 / 255.0);
    } else if (height >= 2 && height < 3) {
        rgb = glm::vec3(147.0 / 255.0, 85.0 / 255.0, 46.0 / 255.0);
    } else if (height >= 3 && height < 4) {
        rgb = glm::vec3(121.0 / 255.0, 58.0 / 255.0, 46.0 / 255.0);
    } else if (height >= 4 && height < 6) {
        rgb = glm::vec3(142.0 / 255.0, 95.0 / 255.0, 70.0 / 255.0);
    } else if (height >= 6 && height < 7) {
        rgb = glm::vec3(228.0 / 255.0, 198.0 / 255.0, 171.0 / 255.0);
    } else if (height >= 7 && height < 9) {
        rgb = glm::vec3(168.0 / 255.0, 108.0 / 255.0, 21.0 / 255.0);
    } else if (height >= 9 && height < 11) {
        rgb = glm::vec3(121.0 / 255.0, 58.0 / 255.0, 46.0 / 255.0);
    } else if (height >= 11 && height < 12) {
        rgb = glm::vec3(147.0 / 255.0, 85.0 / 255.0, 46.0 / 255.0);
    } else if (height >= 12 && height < 13) {
        rgb = glm::vec3(79.0 / 255.0, 39.0 / 255.0, 28.0 / 255.0);
    } else if (height >= 13 && height < 14) {
        rgb = glm::vec3(.5, .35, .22);
    } else if (height >= 14 && height < 15) {
        rgb = glm::vec3(79.0 / 255.0, 39.0 / 255.0, 28.0 / 255.0);
    } else if (height >= 15 && height < 17) {
        rgb = glm::vec3(142.0 / 255.0, 95.0 / 255.0, 70.0 / 255.0);
    } else if (height >= 22) {
        rgb = glm::vec3(1.0, 1.0, 1.0);
    } else {
        rgb = glm::vec3(177.0 / 255.0, 105.0 / 255.0, 50.0 / 255.0);
    }
    //std::cout << "HELLO BLOCK" << std::endl;
    glm::vec3 min(x_start, y_start, z_start);
    glm::vec3 max(x_start + size, y_start + size, z_start + size);
    //front
    //bot left
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart, arrayStart + 1, arrayStart + 2));

    //top right
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 3, arrayStart + 4, arrayStart + 5));

    //back-------------------------------------------------------
    //botleft

    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 6, arrayStart + 7, arrayStart + 8));

    //top right

    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 9, arrayStart + 10, arrayStart + 11));

    //top---------------------------------------------------------
    //botleft

    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 12, arrayStart + 13, arrayStart + 14));

    //top right
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 15, arrayStart + 16, arrayStart + 17));

    //bottom--------------------------------------------------------
    //botleft

    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 18, arrayStart + 19, arrayStart + 20));

    //top right

    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 21, arrayStart + 22, arrayStart + 23));

    //right--------------------------------------------------------
    //botleft
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 24, arrayStart + 25, arrayStart + 26));

    //top right

    block_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 27, arrayStart + 28, arrayStart + 29));

    //left--------------------------------------------------------
    //botleft
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 30, arrayStart + 31, arrayStart + 32));

    //top right
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 33, arrayStart + 34, arrayStart + 35));

    //std::cout << "HELLO BLOCK 1" << std::endl;
}
