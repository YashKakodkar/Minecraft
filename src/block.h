#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>
#include <vector>

class Block {
public:
    Block();

    ~Block();

    void set_nesting_level(int);

    bool is_dirty() const;

    void set_clean();

    void draw_block(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces,
        float minx, float miny, float minz, float maxx, float maxy, float maxz, int arrayStart) const;

    void generate_geometry(std::vector<glm::vec4>& obj_vertices,
        std::vector<glm::uvec3>& obj_faces) const;

    int recursive_box(std::vector<glm::vec4>& obj_vertices, std::vector<glm::uvec3>& obj_faces, float length,
        float minx, float miny, float minz, int level, int arrayStart) const;

private:
    int nesting_level_ = 0;
    bool dirty_ = false;
};

#endif