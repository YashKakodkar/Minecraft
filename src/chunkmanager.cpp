#include "chunkmanager.h"
#include "iostream"
Chunkmanager::Chunkmanager()
{
    for (int i = -4; i < 5; i++) {
        for (int j = -4; j < 5; j++) {
            //std::cout << "i: " << i << "j : " << j << std::endl;
            Chunk curr(i * 16, j * 16);
            allChunks.push_back(curr);
        }
    }
}

Chunkmanager::~Chunkmanager()
{
    allChunks.clear();
    chuncksToRender.clear();
}
