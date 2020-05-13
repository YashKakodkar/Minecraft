// #include <vector>
// #include <string>
// class Skybox {
// public:
//     Skybox(int width, int height);
//     unsigned int loadSkybox(int width, int height);
//     void createBuffers();
// 	~Skybox();
//     const float skyboxVertices[108] = {
//         // positions
//         -1.0f,  1.0f, -1.0f,
//         -1.0f, -1.0f, -1.0f,
//          1.0f, -1.0f, -1.0f,
//          1.0f, -1.0f, -1.0f,
//          1.0f,  1.0f, -1.0f,
//         -1.0f,  1.0f, -1.0f,

//         -1.0f, -1.0f,  1.0f,
//         -1.0f, -1.0f, -1.0f,
//         -1.0f,  1.0f, -1.0f,
//         -1.0f,  1.0f, -1.0f,
//         -1.0f,  1.0f,  1.0f,
//         -1.0f, -1.0f,  1.0f,

//          1.0f, -1.0f, -1.0f,
//          1.0f, -1.0f,  1.0f,
//          1.0f,  1.0f,  1.0f,
//          1.0f,  1.0f,  1.0f,
//          1.0f,  1.0f, -1.0f,
//          1.0f, -1.0f, -1.0f,

//         -1.0f, -1.0f,  1.0f,
//         -1.0f,  1.0f,  1.0f,
//          1.0f,  1.0f,  1.0f,
//          1.0f,  1.0f,  1.0f,
//          1.0f, -1.0f,  1.0f,
//         -1.0f, -1.0f,  1.0f,

//         -1.0f,  1.0f, -1.0f,
//          1.0f,  1.0f, -1.0f,
//          1.0f,  1.0f,  1.0f,
//          1.0f,  1.0f,  1.0f,
//         -1.0f,  1.0f,  1.0f,
//         -1.0f,  1.0f, -1.0f,

//         -1.0f, -1.0f, -1.0f,
//         -1.0f, -1.0f,  1.0f,
//          1.0f, -1.0f, -1.0f,
//          1.0f, -1.0f, -1.0f,
//         -1.0f, -1.0f,  1.0f,
//          1.0f, -1.0f,  1.0f
//     };
//     const std::vector<std::string> faces{
//         "terrain_positive_x.jpg",
//         "terrain_negative_x.jpg",
//         "terrain_positive_y.jpg",
//         "terrain_negative_y.jpg",
//         "terrain_positive_z.jpg",
//         "terrain_negative_z.jpg"
//     };
//     unsigned int textureID;
// };