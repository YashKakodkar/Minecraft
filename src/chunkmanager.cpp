#include "chunkmanager.h"
#include "iostream"
<<<<<<< HEAD
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
=======
#include <glm/gtx/string_cast.hpp>

Chunkmanager::Chunkmanager() {
	for (int i = -4; i < 5; i++) {
		for (int j = -4; j < 5; j++) {
			Chunk curr(i * 16, j * 16);
			RenderDataInput temp;
			temp.assign(0, "vertex_position", curr.block_vertices.data(), curr.block_vertices.size(), 4, GL_FLOAT);
			temp.assignIndex(curr.block_faces.data(), curr.block_faces.size(), 3);
			
			allChunks.push_back(curr);
		}
	}
}

Chunkmanager::Chunkmanager(int vao, const std::vector<const char*> shaders, const std::vector<ShaderUniformPtr> uniforms, const std::vector<const char*> output)
{
	allChunks.clear();
	toRender.clear();
	chuncksToRender.clear();
	this->shaders = shaders;
	this->uniforms = uniforms;
	this->output = output;
	for (int i = -3; i < 3; i++) {
		for (int j = -3; j < 3; j++) {
			//std::cout << "i: " << i << "j : " << j << std::endl;
			Chunk curr(i * 16, j * 16);
			chunk_size = curr.block_faces.size() * 3;
			//std::cout << curr.block_vertices.size() << "block vert : \n";
			//std::cout << curr.block_faces.size() << "block face: \n";
			RenderDataInput temp;
			temp.assign(0, "vertex_position", curr.block_vertices.data(), curr.block_vertices.size(), 4, GL_FLOAT);
			temp.assignIndex(curr.block_faces.data(), curr.block_faces.size(), 3);
			toRender.push_back(std::make_unique<RenderPass>(-1, temp, shaders, uniforms, output));
			allChunks.push_back(curr);
		}
	}
}


void Chunkmanager::render() {
	for (int i = 0; i < toRender.size(); i++) {
		toRender[i]->setup();
		glDrawElements(GL_TRIANGLES,
			chunk_size,
			GL_UNSIGNED_INT, 0);
	}

}

void Chunkmanager::render(glm::vec3 center) {
	createChunksInCircle(center);
	for (int i = 0; i < toRender.size(); i++) {
		toRender[i]->setup();
		glDrawElements(GL_TRIANGLES,
			chunk_size,
			GL_UNSIGNED_INT, 0);
	}

}

void Chunkmanager::createChunksInCircle(glm::vec3 center) {
	int name[6][6] = { {0,0,0,0,0,0},
						{0,0,0,0,0,0}, 
						{0,0,0,0,0,0}, 
						{0,0,0,0,0,0}, 
						{0,0,0,0,0,0}};

	if (toRender.size() > 50) {
		eraseFrontofRender();
	}
	if (allChunks.size() > 100) {
		eraseFrontofChunk();
	}
	for (int i = -3; i < 3; i++) {
		for (int j = -3; j < 3; j++) {
			for (int index = 0; index < allChunks.size(); index++) {
				int xNeed = (((int)(center.x + i * 16) / 16) * 16);
				int zNeed = (((int)(center.z + j * 16) / 16) * 16);
				if (allChunks[index].x_length == xNeed && allChunks[index].z_length == zNeed) {
					name[i + 3][j + 3] = 1;
					break;
				}
			}
		}
	}

	for (int i = -3; i < 3; i++) {
		for (int j = -3; j < 3; j++) {
			if (name[i+3][j+3] == 0) {
				int xNeed = (((int)(center.x + i * 16) / 16) * 16);
				int zNeed = (((int)(center.z + j * 16) / 16) * 16);
				Chunk curr(xNeed, zNeed);
				RenderDataInput temp;
				temp.assign(0, "vertex_position", curr.block_vertices.data(), curr.block_vertices.size(), 4, GL_FLOAT);
				temp.assignIndex(curr.block_faces.data(), curr.block_faces.size(), 3);
				toRender.push_back(std::make_unique<RenderPass>(-1, temp, shaders, uniforms, output));
				allChunks.push_back(curr);
			}
		}
	}

}

void Chunkmanager::eraseFrontofChunk() {
	allChunks.erase(allChunks.begin(), allChunks.begin() + allChunks.size()/10);
}

void Chunkmanager::eraseFrontofRender() {
	toRender.erase(toRender.begin(), toRender.begin() + toRender.size() / 10);
}

Chunkmanager::~Chunkmanager() {
	allChunks.clear();
	toRender.clear();
	chuncksToRender.clear();
>>>>>>> 43291c497e04cd534ffaccc95423f1356fc9de8c
}
