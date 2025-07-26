#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <glad/glad.h>
#include "log.hpp"

#if !defined(__ANDROID__)
#include <GLFW/glfw3.h>
struct GLFWwindowDeleter {
    void operator()(GLFWwindow* window) const {
        if (window) {
            glfwDestroyWindow(window);
        }
    }
};
#endif

class Renderer {
private:
#if !defined(__ANDROID__)
    std::unique_ptr<GLFWwindow, GLFWwindowDeleter> m_window;
    bool m_shouldWindowClose = false;
#endif
public:
    bool init();
    void compileShaders();
    void draw();

#if !defined(__ANDROID__)
    GLFWwindow* getWindow() const;
#endif
};

#endif // RENDERER_H