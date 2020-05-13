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
	for (int i = -4; i < 5; i++) {
		for (int j = -4; j < 5; j++) {
			std::cout << "i: " << i << "j : " << j << std::endl;
			Chunk curr(i * 16, j * 16);
			std::cout << curr.block_vertices.size() << "block vert : \n";
			std::cout << curr.block_faces.size() << "block face: \n";
			RenderDataInput temp;
			temp.assign(0, "vertex_position", curr.block_vertices.data(), curr.block_vertices.size(), 4, GL_FLOAT);
			temp.assignIndex(curr.block_faces.data(), curr.block_faces.size(), 3);
			RenderPass temp2(-1, temp, shaders, uniforms, output);
			toRender.push_back(&temp2);
			//toRender.push_back(&curr_pass);
			allChunks.push_back(curr);
		}
	}
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
	chuncksToRender.clear();
}

