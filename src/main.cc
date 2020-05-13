#include <GL/glew.h>
// #ifdef _WIN32
// #include <direct.h>
// #else
// #include <sys/stat.h>
// #endif
#include "block.h"
#include "chunk.h"
#include "chunkmanager.h"
#include "config.h"
#include "gui.h"
#include "jpegio.h"
#include "procedure_geometry.h"
#include "render_pass.h"
#include "skybox.h"
#include <algorithm>
#include <debuggl.h>
#include <fstream>
#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <string>
#include <vector>

int window_width = 800, window_height = 600;
const std::string window_title = "Minecraft";

const char* vertex_shader =
#include "shaders/default.vert"
    ;

const char* blending_shader =
#include "shaders/blending.vert"
    ;

const char* geometry_shader =
#include "shaders/default.geom"
    ;

const char* fragment_shader =
#include "shaders/default.frag"
    ;

const char* floor_fragment_shader =
#include "shaders/floor.frag"
    ;

const char* cube_vertex_shader =
#include "shaders/cube.vert"
    ;

const char* cube_geometry_shader =
#include "shaders/cube.geom"
    ;

const char* cube_fragment_shader =
#include "shaders/cube.frag"
    ;

const char* skybox_vertex_shader =
#include "shaders/skybox.vert"
    ;

const char* skybox_fragment_shader =
#include "shaders/skybox.frag"
    ;

// FIXME: Add more shaders here.

void ErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << "\n";
}

GLFWwindow* init_glefw()
{
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwSetErrorCallback(ErrorCallback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    auto ret = glfwCreateWindow(window_width, window_height, window_title.data(), nullptr, nullptr);
    CHECK_SUCCESS(ret != nullptr);
    glfwMakeContextCurrent(ret);
    glewExperimental = GL_TRUE;
    CHECK_SUCCESS(glewInit() == GLEW_OK);
    glGetError(); // clear GLEW's error for it
    glfwSwapInterval(1);
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
   // std::cout << "Renderer: " << renderer << "\n";
    //std::cout << "OpenGL version supported:" << version << "\n";

    return ret;
}

int main(int argc, char* argv[])
{

    GLFWwindow* window = init_glefw();
    GUI gui(window);

    glm::vec4 light_position = glm::vec4(0.0f, 100.0f, 0.0f, 1.0f);
    MatrixPointers mats; // Define MatrixPointers here for lambda to capture
    //
    //std::cout << "che\n";
    /*
	 * In the following we are going to define several lambda functions as
	 * the data source of GLSL uniforms
	 *
	 * Introduction about lambda functions:
	 *      http://en.cppreference.com/w/cpp/language/lambda
	 *      http://www.stroustrup.com/C++11FAQ.html#lambda
	 *
	 * Note: lambda expressions cannot be converted to std::function directly
	 *       Hence we need to declare the data function explicitly.
	 *
	 * CAVEAT: DO NOT RETURN const T&, which compiles but causes
	 *         segfaults.
	 *
	 * Do not worry about the efficient issue, copy elision in C++ 17 will
	 * minimize the performance impact.
	 *
	 * More details about copy elision:
	 *      https://en.cppreference.com/w/cpp/language/copy_elision
	 */

    // FIXME: add more lambdas for data_source if you want to use RenderPass.
    //        Otherwise, do whatever you like here
    std::function<const glm::mat4*()> model_data = [&mats]() {
    //    std::cout << "herejiasodhioashdoi";
        return mats.model;
    };
    std::function<glm::mat4()> view_data = [&mats]() { return *mats.view; };
    std::function<glm::mat4()> proj_data = [&mats]() { return *mats.projection; };
    std::function<glm::mat4()> identity_mat = []() { return glm::mat4(1.0f); };
    std::function<glm::vec3()> cam_data = [&gui]() { return gui.getCamera(); };
    std::function<glm::vec4()> lp_data = [&light_position]() { return light_position; };
    //std::function<std::vector<glm::vec3>()> chunk_pos_data = [&terrain]() { return terrain.block_positions; };

    auto std_model = std::make_shared<ShaderUniform<const glm::mat4*>>("model", model_data);
    auto floor_model = make_uniform("model", identity_mat);
    auto std_view = make_uniform("view", view_data);
    auto std_camera = make_uniform("camera_position", cam_data);
    auto std_proj = make_uniform("projection", proj_data);
    auto std_light = make_uniform("light_position", lp_data);
    //auto chunk_pos = make_uniform("chunk_pos", chunk_pos_data);

    std::function<float()> alpha_data = [&gui]() {
        static const float transparet = 0.5; // Alpha constant goes here
        static const float non_transparet = 1.0;
        if (gui.isTransparent())
            return transparet;
        else
            return non_transparet;
    };
    auto object_alpha = make_uniform("alpha", alpha_data);

    // Otherwise, do whatever you like here
    //Cube render pass

    Chunkmanager testing(-1,
        { cube_vertex_shader, nullptr, cube_fragment_shader },
        { floor_model, std_view, std_proj, std_light },
        { "fragment_color" });
    float aspect = 0.0f;
    bool draw_floor = true;
    bool draw_cube = true;
    int index = 0;
    //return 0;
    while (!glfwWindowShouldClose(window)) {
     //   std::cout << glfwGetTime()  << " time\n";
        if ((int)glfwGetTime() % 2 == 0) {

        }
        // Setup some basic window stuff.
        glfwGetFramebufferSize(window, &window_width, &window_height);
        glViewport(0, 0, window_width, window_height);
        glm::dvec3 b = glm::vec3(13.0 / 255, 20.0 / 255, 25.0 / 255);
        glm::dvec3 w = glm::vec3(135.0 / 255, 206.0 / 255, 250.0 / 255);
        glm::vec4 lerp;
        int time = 20;
        if (((int)glfwGetTime() / time) % 2 == 0) {
            lerp = glm::vec4(glm::mix(b, w, ((int)glfwGetTime() % time) / (double)time), 1.0f);
        }
        else {
            lerp = glm::vec4(glm::mix(w, b, ((int)glfwGetTime() % time) / (double)time), 1.0f);
        }

        glClearColor(lerp[0],lerp[1], lerp[2], 0.0f);
        
        
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        gui.updateMatrices();
        mats = gui.getMatrixPointers();

#if 0
		std::cerr << model_data() << '\n';
		std::cerr << "call from outside: " << std_model->data_source() << "\n";
		std_model->bind(0);
#endif

        if (gui.isPoseDirty()) {
            gui.clearPose();
        }

        if (draw_cube) {
            //glActiveTexture(GL_TEXTURE1);
            //glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
            testing.render(gui.getCenter());
        }
        index = 1;
        // Poll and swap.
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
