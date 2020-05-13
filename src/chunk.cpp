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

    //create_block(0.0f,0.0f,0.0f,1.0f);
    //generate_plane(x_length, z_length);
    create_mesh(x_length, -CHUNK_SIZE, z_length);
    //std::cout << "HELLO DONE" << std::endl;
    //create_mesh2(x_length, -16, z_length);
}

//Chunk::~Chunk()
//{
//    // Delete the blocks
//    //for (int i = 0; i < CHUNK_SIZE; ++i) {
//    //    for (int j = 0; j < CHUNK_SIZE; ++j) {
//    //        if (blocks[i][j] != NULL) {
//    //            delete[] blocks[i][j];
//    //        }
//    //    }
//    //    if (blocks[i] != NULL) {
//    //        delete[] blocks[i];
//    //    }
//    //
//    //}
//    //if (blocks != NULL) {
//    //    delete[] blocks;
//    //}
//    block_faces.clear();
//    block_vertices.clear();
//}

void Chunk::create_mesh(int x_grid, int y_grid, int z_grid)
{
    int arrayStart = 0;
    int i = 0;
    int high = 10;
    int low = 6;
    int prevHeight = 8;
    perlin.generateHeightMap(x_grid + 8, z_grid + 8);
    std::cout << "Test heights" << std::endl;
    for (int i = 0; i < 16; i++) {
        for (int r = 0; r < 16; r++) {
            std::cout << perlin.height_map_[i][r] << "    ";
            //x++;
        }
        std::cout << std::endl;
    }
    //std::cout << "HELLO 7" << std::endl;
    //std::vector<std::vector<int>> height_map = perlin.height_map_; //std::vector<std::vector<int>>(16, std::vector<int>(16, 0));
    //std::cout << "HELLO 8" << std::endl;
    //int height_map[16][16] = { 0 };
    //height_map = perlin.height_map_;
    std::cout << "Begin Chunk " << x_grid << ", " << z_grid << std::endl;

    for (int x = 0; x < 16; ++x) {
        //std::cout << "\nNEW X\n"<< std::endl;
        for (int z = 0; z < 16; ++z) {
            //std::cout << "\nNEW Y\n"<< std::endl;
            //std::cout << "HELLO 10" << std::endl;
            int height = perlin.height_map_[x][z]; // std::rand() % (high - low) + low;
            //std::cout << "HELcLO 11" << std::endl;
            //std::cout << "x: " << x << " |  z: " << z << "  | HEIGHT: " << height << std::endl;

            for (int y = 0; y < height; ++y) {
                // if (blocks[x][y][z].is_active() == false) {
                //     continue;
                // }
                //std::cout << "X: " << x << "  | Y: " << y << "  | Z: " << z << "  | CHUNK_SIZE: " << CHUNK_SIZE << std::endl;
                // std::cout << "HELLO 10  | HEIGHT: " << 0 << std::endl;
                create_block(x_grid + x, y_grid + y, z_grid + z, 1, arrayStart);
                if (y == height - 1) {
                    std::cout << y << "  ";
                }

                //std::cout << "Grid Pos #: " << i << "  | " << x_grid + x << " " << y_grid + y << " " << z_grid + z << std::endl;
                i++;
                arrayStart += 36;
            }

            // if (height > prevHeight) {

            //     high = std::min(high + 2, 16);
            //     low = std::min(low + 2, 12);
            // } else if (height < prevHeight) {
            //     high = std::max(high - 2, 4);
            //     low = std::max(low - 2, 0);
            // }
            // prevHeight = height;
        }
        std::cout << std::endl;
    }
    //std::cout << block_vertices.size() << "terrain vert size" << std::endl;
    //std::cout << block_faces.size() << "terrain face size" << std::endl;
}

void Chunk::create_mesh(int x_grid, int z_grid)
{
    for (int x = 0; x < CHUNK_SIZE; x++) {

        for (int z = 0; z < CHUNK_SIZE; z++) {
            if (blocks[x][0][z].is_active() == false) {
                continue;
            }
            block_positions.push_back(glm::vec3(x + (CHUNK_SIZE * x_grid), 0, z + (CHUNK_SIZE * z_grid)) * 0.5f);
        }
    }
}
void Chunk::generate_plane(int x_len, int z_len)
{
    block_positions.clear();
    for (int x = 0; x < x_length; x++) {
        for (int z = 0; z < z_length; z++) {
            create_mesh(x, z);
        }
    }
}

void Chunk::create_mesh2(int x_grid, int y_grid, int z_grid)
{
    int arrayStart = 0;
    std::srand(std::time(nullptr));
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                // if (blocks[x][y][z].is_active() == false) {
                //     continue;
                // }

                create_blockC(x_grid + x, -16, z_grid + z, 1, arrayStart);

                arrayStart += 36;
            }
        }
    }
}

//void Chunk::generate_cube()
void Chunk::create_block(float x_start, float y_start, float z_start, float size, int arrayStart)
{

    //std::cout << "HELLO BLOCK" << std::endl;
    glm::vec3 min(x_start, y_start, z_start);
    glm::vec3 max(x_start + size, y_start + size, z_start + size);
    //front
    //bot left
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart, arrayStart + 1, arrayStart + 2));

    //top right
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 3, arrayStart + 4, arrayStart + 5));

    //back-------------------------------------------------------
    //botleft

    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 6, arrayStart + 7, arrayStart + 8));

    //top right

    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 9, arrayStart + 10, arrayStart + 11));

    //top---------------------------------------------------------
    //botleft

    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 12, arrayStart + 13, arrayStart + 14));

    //top right
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 15, arrayStart + 16, arrayStart + 17));

    //bottom--------------------------------------------------------
    //botleft
    block_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 18, arrayStart + 19, arrayStart + 20));

    //top right
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 21, arrayStart + 22, arrayStart + 23));

    //right--------------------------------------------------------
    //botleft
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 24, arrayStart + 25, arrayStart + 26));

    //top right

    block_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 27, arrayStart + 28, arrayStart + 29));

    //left--------------------------------------------------------
    //botleft
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 30, arrayStart + 31, arrayStart + 32));

    //top right
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 33, arrayStart + 34, arrayStart + 35));

    //std::cout << "HELLO BLOCK 1" << std::endl;
}

void Chunk::create_blockC(float x_start, float y_start, float z_start, float size, int arrayStart)
{
    glm::vec3 rgb = glm::vec3(1.0, 1.0, 1.0);
    if (y_start >= -16 && y_start < -12) {
        rgb = glm::vec3(1.0, 0.0, 0.0);
    }
    if (y_start >= -11 && y_start < -2) {
        rgb = glm::vec3(1.0, 1.0, 0.0);
    }
    if (y_start >= -2 && y_start < 5) {
        rgb = glm::vec3(0.0, 0.0, 1.0);
    }
    if (y_start >= 5) {
        rgb = glm::vec3(0.0, 1.0, 0.0);
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
    block_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_color.push_back(rgb);
    block_faces.push_back(glm::uvec3(arrayStart + 18, arrayStart + 19, arrayStart + 20));

    //top right
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
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

void Chunk::create_block(int size)
{
    glm::vec3 min(-size, -size, -size);
    glm::vec3 max(size, size, size);
    int arrayStart = 0;

    //front
    //bot left
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart, arrayStart + 1, arrayStart + 2));

    //top right
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 3, arrayStart + 4, arrayStart + 5));

    //back-------------------------------------------------------
    //botleft

    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 6, arrayStart + 7, arrayStart + 8));

    //top right

    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 9, arrayStart + 10, arrayStart + 11));

    //top---------------------------------------------------------
    //botleft

    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 12, arrayStart + 13, arrayStart + 14));

    //top right
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 15, arrayStart + 16, arrayStart + 17));

    //bottom--------------------------------------------------------
    //botleft
    block_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 18, arrayStart + 19, arrayStart + 20));

    //top right
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 21, arrayStart + 22, arrayStart + 23));

    //right--------------------------------------------------------
    //botleft
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 24, arrayStart + 25, arrayStart + 26));

    //top right

    block_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 27, arrayStart + 28, arrayStart + 29));

    //left--------------------------------------------------------
    //botleft
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 30, arrayStart + 31, arrayStart + 32));

    //top right
    block_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
    block_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
    block_faces.push_back(glm::uvec3(arrayStart + 33, arrayStart + 34, arrayStart + 35));
}