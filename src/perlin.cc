#include "perlin.h"
#include <algorithm>
#include <chrono> // std::chrono::system_clock
#include <cmath>
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

    for (int i = 0; i < 256; i++) {
        p[i] = p[i + 256] = permutation[i];
    }
}

double Perlin::noise(double x, double y, double z)
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
    int AAA = p[X] + Y;
    int AAB = p[AAA] + Z;
    int ABA = p[AAA + 1] + Z;
    int BBB = p[X + 1] + Y;
    int BAB = p[BBB] + Z;
    int BBA = p[BBB + 1] + Z;
    //std::cout << "HELLO 4" << std::endl;
    return lerp(w, lerp(v, lerp(u, grad(p[AAB], x, y, z), grad(p[BAB], x - 1, y, z)), lerp(u, grad(p[ABA], x, y - 1, z), grad(p[BBA], x - 1, y - 1, z))),
        lerp(v, lerp(u, grad(p[AAB + 1], x, y, z - 1), grad(p[BAB + 1], x - 1, y, z - 1)),
            lerp(u, grad(p[ABA + 1], x, y - 1, z - 1),
                grad(p[BBA + 1], x - 1, y - 1, z - 1))));
}

int Perlin::inc(int num)
{
    num++;
    if (repeat > 0)
        num %= (int)repeat;

    return num;
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
    int h = hash & 15;
    double u = h < 8 ? x : y,
           v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

Perlin::~Perlin()
{
}

void Perlin::create_height_map(int x, int z)
{

    float chunk_x = x, chunk_z = z;
    int center_x = std::floor(chunk_x / 1);
    int center_z = std::floor(chunk_z / 1);
    int origin_center_x = 16 / 2;
    int origin_center_z = 16 / 2;

    x_shift = -1 * (center_x - origin_center_x);
    z_shift = -1 * (center_z - origin_center_z);

    for (int x = 0; x < 16; x++) {
        //std::cout << "HELLO 1" << std::endl;
        for (int z = 0; z < 16; z++) {
            int pos_x = x + x_shift;
            int pos_z = z + z_shift;

            int y = std::floor(amp * abs((float)noise(pos_x * freq, 0.0, pos_z * freq)));
            if (y == 0) {
                y = 2;
            }
            height_map_[x][z] = y;
        }
    }
}