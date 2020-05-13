#include "chunk.h"
#include <vector>
#include "render_pass.h"
#include "gui.h"
#pragma once
class Chunkmanager {
public:
    Chunkmanager();
    Chunkmanager(int vao, // -1: create new VAO, otherwise use given VAO
        const std::vector<const char*> shaders, // Order: VS, GS, FS 
        const std::vector<ShaderUniformPtr> uniforms,
        const std::vector<const char*> output // Order: 0, 1, 2...);
    );
    void render();
    void render(glm::vec3 center);
    void createChunksInCircle(glm::vec3 center);
    void eraseFrontofChunk();
    void eraseFrontofRender();
        ~Chunkmanager();
        static const int CHUNKS = 1;
        static const int CHUNK_SIZE = 16;
    private:
        std::vector<std::unique_ptr<Chunk>> allChunks;
        std::vector<const char*> shaders;
        std::vector<ShaderUniformPtr> uniforms;
        std::vector<const char*> output;
        std::vector<Chunk> chuncksToRender;
        std::vector<std::unique_ptr<RenderPass>> toRender;
        int chunk_size = 0;
        
};