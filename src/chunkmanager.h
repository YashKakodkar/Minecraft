#include "chunk.h"
#include <vector>
#include "render_pass.h"
class Chunkmanager{
    public:
        Chunkmanager();
        ~Chunkmanager();
        std::vector<Chunk> getChunks() const { return allChunks; }
    private:
        std::vector<Chunk> allChunks; 
        std::vector<Chunk> chuncksToRender;
        std::vector<RenderDataInput> toRender;
        
};