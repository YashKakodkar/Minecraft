#include "chunk.h"
#include <vector>
#include "render_pass.h"

class RenderPass;
class Chunkmanager {
public:
    Chunkmanager();
    Chunkmanager(int vao, // -1: create new VAO, otherwise use given VAO
        const std::vector<const char*> shaders, // Order: VS, GS, FS 
        const std::vector<ShaderUniformPtr> uniforms,
        const std::vector<const char*> output // Order: 0, 1, 2...);
);
        ~Chunkmanager();
        std::vector<Chunk> getChunks() const { return allChunks; }
    //private:
        std::vector<Chunk> allChunks; 
        std::vector<Chunk> chuncksToRender;
        std::vector<RenderPass*> toRender;
        
};