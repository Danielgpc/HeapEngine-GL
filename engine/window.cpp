#include "window.h"

#include "engine.h"
#include "defines.h"
#include "logger.h"

bool Engine::initWindow() {
  if (!glfwInit()) {
    Logger::log(LogLevel::ERROR, "Failed to initialize GLFW");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window = glfwCreateWindow(WIDTH, HEIGHT, "Heap engine gl window", nullptr,
                            nullptr);
  if (window == nullptr) {
    Logger::log(LogLevel::ERROR, "Failed to create window");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::log(LogLevel::ERROR, "Failed to initialize GLAD");
    return false;
  }

  glfwSetFramebufferSizeCallback(window, Engine::framebuffer_size_callback);
  glViewport(0, 0, WIDTH, HEIGHT);
  return true;
}

void Engine::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void Engine::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  (void)window;
  glViewport(0, 0, width, height);
}
