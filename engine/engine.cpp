#include "engine.h"
#include "GLFW/glfw3.h"
#include "defines.h"

#include <iostream>

void Engine::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void Engine::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  (void)window;
  glViewport(0, 0, width, height);
}

int Engine::init() {
  //> Initialize GLFW and create window
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
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
    std::cout << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  //< Initialize GLFW and create window

  //> Initialize Glad and some OpenGL stuff
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to Initialize GLAD" << std::endl;
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, Engine::framebuffer_size_callback);
  glViewport(0, 0, WIDTH, HEIGHT);
  //<  Initialize Glad and some OpenGL stuff

  std::cout << "Engine initialized.\n";
  return 0;
}

int Engine::run() {
  while (!glfwWindowShouldClose(window)) {
    // input
    Engine::processInput(window);

    // Put things on screen
    render();

    // Check call events and swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return 0;
}

void Engine::render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

int Engine::cleanup() {
  glfwTerminate();
  std::cout << "Engine cleaned up.\n";
  return 0;
}
