#ifndef BLOCK_H
#define BLOCK_H

#include "config.h"
#include <glm/glm.hpp>
#include <vector>

class Block {
public:
    Block();

    ~Block();
    void create_block(std::vector<glm::vec4>& block_vertices, std::vector<glm::uvec3>& block_faces);
    void set_texture(int t) { texture = t; }
    int get_texture() { return texture; }
    void set_activity(bool a) { active = a; }
    bool is_active() { return active; }

    bool test;
    bool is_dirty() const;

    void set_clean();

    void draw_block(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces,
        float minx, float miny, float minz, float maxx, float maxy, float maxz, int arrayStart) const;

    void generate_multiBlocks(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces) const;

    void generate_multiBlocksLenth(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces, float startx, float starty, float startz, float length) const;

private:
    bool dirty_ = false;
    int texture;
    bool active;
};

#endif
