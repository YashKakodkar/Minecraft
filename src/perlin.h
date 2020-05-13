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

    double noise(double x, double y, double z);
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
    int inc(int num);
    void create_height_map(int x, int z);

private:
    std::vector<double> p = std::vector<double>(512, 0);
    int x_shift, z_shift;
    int repeat = 0;
    float freq = 0.05;
    float amp = 24;
};

#endif