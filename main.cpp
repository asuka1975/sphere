#include <iostream>

#include <gl++/vertex_buffer.h>
#include <gl++/vertex_array.h>
#include <gl++/shader.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

    glEnable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 1);
    glfwSetTime(0);
    double fps = 60;
    double previous = glfwGetTime();
    double current = glfwGetTime();
    while(glfwWindowShouldClose(window) == GLFW_FALSE) {
        if(current - previous >= 1.f / fps) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glfwSwapBuffers(window);
            previous = glfwGetTime();
        }

        glfwPollEvents();
        current = glfwGetTime();
    }

    return 0;
}
