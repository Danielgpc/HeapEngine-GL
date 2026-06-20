#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Engine {
public:
  int init();
  int run();
  int cleanup();

private:
  GLFWwindow *window;

  unsigned int VBO, VAO, EBO;
  unsigned int shaderProgram;

  void render();

  void processInput(GLFWwindow *window);
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);

  // Load and compile shaders
  std::string loadShaderSource(const std::string &shaderPath);
  void compileShader(unsigned int shader, const char *shaderSource);
};
