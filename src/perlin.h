#ifndef PERLIN_H
#define PERLIN_H

#include "block.h"
#include "config.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <vector>

class Perlin {
public:
    //std::vector<std::vector<int>> height_map_ = std::vector<std::vector<int>>(16, std::vector<int>(16, 0));
    int height_map_[16][16] = { 0 };
    Perlin();
    ~Perlin();

    double noise3D(double x, double y, double z);
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
    void generateHeightMap(int x, int z);

private:
    std::vector<double> p = { 1.0, 2.0, 3.0 };
    int grid_shift_x_, grid_shift_z_;

    float perlin_freq_ = 0.05; // adjust frequency of perlin noise
    float perlin_height_amp_ = 24; // adjust amplitude of perlin noise
};

#endif