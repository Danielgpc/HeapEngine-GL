#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine {
public:
  int init();
  int run();
  int cleanup();

private:
  GLFWwindow *window;
  void processInput(GLFWwindow *window);
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
  void render();
};
