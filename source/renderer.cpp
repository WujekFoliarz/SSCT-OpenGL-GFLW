#include "renderer.hpp"  
#include <stdexcept>
#include <glad/glad_egl.h>
 
bool Renderer::init() {
#if !defined(__ANDROID__)  
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_window = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>(glfwCreateWindow(1280, 720, PROJECT_NAME, nullptr, nullptr));
    if (!m_window) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(m_window.get());
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glViewport(0, 0, 1280, 720);

    glfwSetWindowCloseCallback(m_window.get(), [](GLFWwindow* window) {
        glfwSetWindowShouldClose(window, true);
    });

    glfwSetWindowSizeCallback(m_window.get(), [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
    
#else
    if (!gladLoadGLES2Loader((GLADloadproc)eglGetProcAddress)) {
        LOGI("Failed to initialize GLAD");
    }
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    
#endif

    return true;
}

#if !defined(__ANDROID__)
GLFWwindow* Renderer::getWindow() const {
    return m_window.get();
}
#endif

void Renderer::compileShaders() {

}

void Renderer::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 1, 0, 1);
}
