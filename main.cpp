#include <iostream>
#include <vector>

#include <gl++/vertex_buffer.h>
#include <gl++/vertex_array.h>
#include <gl++/shader.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <fstream>

int main() {
    if(glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("failed to initialize GLFW");
    }
    std::atexit(glfwTerminate);

    auto window = glfwCreateWindow(700, 700, "sphere", nullptr, nullptr);
    if(window == nullptr) {
        throw std::runtime_error("failed to create GLFWwindow");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) {
        throw std::runtime_error("failed to initialize GLEW");
    }

    std::vector<glm::vec3> vertex {
            { 0, 1, 0 }, { -1, 0, 0 }, { 0, 0, 1 },
            { 1, 0, 0 }, { 0, 0, -1 }, { 0, -1, 0 }
    };
    std::vector<GLuint> index {
        0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 1, 5, 1, 4, 5, 4, 3, 5, 3, 2, 5, 2, 1
    };

    using vertex_traits = gl::buffer_trait<glm::vec3, GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
    using index_traits = gl::buffer_trait<GLuint, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW>;

    gl::vertex_buffer<vertex_traits> vbo(vertex.begin(), vertex.end());
    gl::vertex_buffer<index_traits> ibo(index.begin(), index.end());

    gl::vertex_array vao;
    if(auto ctx = vao.get_bind()) {
        vbo.bind();
        vbo.vertex_pointer(0, GL_FALSE, gl::this_select);
        ibo.bind();
    }

    std::vector<std::pair<std::string, GLenum>> shaders {
            { "../shaders/sphere.vert", GL_VERTEX_SHADER },
            { "../shaders/sphere.frag", GL_FRAGMENT_SHADER }
    };
    gl::shader_program program;
    for(auto& [file, type] : shaders) {
        if(std::ifstream fin(file, std::ios::in); fin.good()) {
            program.add_shader(std::string { std::istreambuf_iterator<GLchar>{fin}, std::istreambuf_iterator<GLchar>{} }, type);
        }
    }
    program.link();

    glEnable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 1);
    glfwSetTime(0);
    double fps = 60;
    double previous = glfwGetTime();
    double current = glfwGetTime();
    while(glfwWindowShouldClose(window) == GLFW_FALSE) {
        if(current - previous >= 1.f / fps) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            program.use();
            vao.bind();
            glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, nullptr);
            vao.unbind();
            program.unuse();

            glfwSwapBuffers(window);
            previous = glfwGetTime();
        }

        glfwPollEvents();
        current = glfwGetTime();
    }

    return 0;
}
