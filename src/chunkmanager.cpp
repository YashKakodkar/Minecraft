#include "chunkmanager.h"
#include "iostream"
Chunkmanager::Chunkmanager() {
	for (int i = -4; i < 5; i++) {
		for (int j = -4; j < 5; j++) {
			std::cout << "i: " << i << "j : " << j << std::endl;
			Chunk curr(i * 16, j * 16);
			RenderDataInput temp;
			temp.assign(0, "vertex_position", curr.block_vertices.data(), curr.block_vertices.size(), 4, GL_FLOAT);
			temp.assignIndex(curr.block_faces.data(), curr.block_faces.size(), 3);
			
			allChunks.push_back(curr);
		}
	}
}

Chunkmanager::Chunkmanager(int vao, const std::vector<const char*> shaders, const std::vector<ShaderUniformPtr> uniforms, const std::vector<const char*> output )
{
	allChunks.clear();
	toRender.clear();
	chuncksToRender.clear();
	for (int i = -4; i < 5; i++) {
		for (int j = -4; j < 5; j++) {
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
	std::cout << "render " <<  toRender[toRender.size() - 1]->getVAO() << std::endl;
	std::cout << "render " <<  toRender.size() << std::endl;
}
//RenderDataInput floor_pass_input;
//floor_pass_input.assign(0, "vertex_position", floor_vertices.data(), floor_vertices.size(), 4, GL_FLOAT);
//floor_pass_input.assignIndex(floor_faces.data(), floor_faces.size(), 3);
//RenderPass floor_pass(-1,
//	floor_pass_input,
//	{ vertex_shader, geometry_shader, floor_fragment_shader },
//	{ floor_model, std_view, std_proj, std_light },
//	{ "fragment_color" }
//);
Chunkmanager::~Chunkmanager() {
	allChunks.clear();
	toRender.clear();
	chuncksToRender.clear();
}

