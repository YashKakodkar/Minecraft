#include "perlin.h"
#include <algorithm>
#include <chrono> // std::chrono::system_clock
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <random> // std::default_random_engine
#include <vector>

Perlin::Perlin()
{
    std::vector<int> permutation = { 151, 160, 137, 91, 90, 15,
        131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
        190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
        88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
        77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
        102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196,
        135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123,
        5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
        223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
        129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
        251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
        49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
        138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180 };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(permutation.begin(), permutation.end(), std::default_random_engine(seed));

    p.resize(512);
    for (int i = 0; i < 256; i++) {
        p[i] = p[i + 256] = permutation[i];
    }
}

double Perlin::noise3D(double x, double y, double z)
{
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;
    //std::cout << "HELLO 2" << std::endl;
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);

    double u = fade(x);
    double v = fade(y);
    double w = fade(z);
    //std::cout << "HELLO 3" << std::endl;
    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z, // HASH COORDINATES OF
        B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z; // THE 8 CUBE CORNERS,
    //std::cout << "HELLO 4" << std::endl;
    return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), // AND ADD
                               grad(p[BA], x - 1, y, z)), // BLENDED
                       lerp(u, grad(p[AB], x, y - 1, z), // RESULTS
                           grad(p[BB], x - 1, y - 1, z))), // FROM  8
        lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), // CORNERS
                    grad(p[BA + 1], x - 1, y, z - 1)), // OF CUBE
            lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

double Perlin::fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double Perlin::lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

double Perlin::grad(int hash, double x, double y, double z)
{
    int h = hash & 15; // CONVERT LO 4 BITS OF HASH CODE
    double u = h < 8 ? x : y, // INTO 12 GRADIENT DIRECTIONS.
        v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

Perlin::~Perlin()
{
}

// Tools

void Perlin::generateHeightMap()
{
    //height_map_.clear();

    float center_x = 0, center_z = 0;
    int grid_center_x = std::floor(center_x / 1), grid_center_z = std::floor(center_z / 1);
    int origin_grid_center_x = 16 / 2, origin_grid_center_z = 16 / 2;

    grid_shift_x_ = -1 * (grid_center_x - origin_grid_center_x);
    grid_shift_z_ = -1 * (grid_center_z - origin_grid_center_z);

    for (int grid_x = 0; grid_x < 16; grid_x++) {
        //std::cout << "HELLO 1" << std::endl;
        for (int grid_z = 0; grid_z < 16; grid_z++) {
            int pos_x = grid_x + grid_shift_x_;
            int pos_z = grid_z + grid_shift_z_;

            //std::cout << pos_x << ", " << pos_z << std::endl;
            int grid_y = std::floor(perlin_height_amp_ * abs((float)noise3D(pos_x * perlin_freq_, 0.0, pos_z * perlin_freq_)));
            // std::cout << "HELLO 5" << std::endl;
            // std::cout << "grid_x = " << grid_x << " | grid_z = " << grid_z << std::endl;
            //std::cout << "grid_y = " << grid_y << std::endl;
            if (grid_y == 0) {
                grid_y = 1;
            }
            height_map_[grid_x][grid_z] = grid_y;

            // if (grid_x == 0 && grid_z == 63) {
            //     std::cout << "[0, 63]! grid_y = " << height_map_[grid_x][grid_z] << std::endl;
            // }
        }
    }
    std::cout << "VALUES DONE" << std::endl;
    int x = 1;
    // for (int i = 0; i < 16; i++) {
    //     for (int r = 0; r < 16; r++) {
    //         std::cout << "#: " << x << " | height: " << height_map_[i][r] << std::endl;
    //         x++;
    //     }
    // }
    // for (int i = 0; i < 16; i++) {
    //     for (int r = 0; r < 16; r++) {
    //         std::cout << height_map_[i][r] << "    ";
    //         x++;
    //     }
    //     std::cout << std::endl;
    // }
    std::cout << "Done" << std::endl;
}