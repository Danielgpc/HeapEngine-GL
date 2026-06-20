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
  GLFWwindow *window = nullptr;

  unsigned int VBO = 0;
  unsigned int VAO = 0;
  unsigned int EBO = 0;
  unsigned int shaderProgram = 0;

  void render();
  bool initWindow();
  bool initShaders();
  void initMesh();

  void processInput(GLFWwindow *window);
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);

  std::string loadShaderSource(const std::string &shaderPath);
  void compileShader(unsigned int shader, const char *shaderSource);
};
