#include "engine.h"
#include "GLFW/glfw3.h"
#include "defines.h"

#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

  //> Load and compile shdaers
  // Vertex shader
  std::string source = loadShaderSource("shaders/shader.vert");
  const char *vertexShaderSource = source.c_str();
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  compileShader(vertexShader, vertexShaderSource);

  // Fragment shader
  source = loadShaderSource("shaders/shader.frag");
  const char *fragmentShaderSource = source.c_str();
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  compileShader(fragmentShader, fragmentShaderSource);

  // Shader program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Check if linking was successfull
  char infoLog[512];
  int success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cout << "ERROR::Shader program linking failed\n"
              << infoLog << std::endl;
  }
  // Cleanup shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  //< Load and compile shaders

  //> Initialize Opengl objects
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  //< Initialize Opengl objects

  // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // Allocate vertices data to the GPU
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Tell OpenGL how to interpret the vertex atribute data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
  // Show green background
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw fisrt triangle
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  // glBindVertexArray(0); no need to unbind everytime
}

int Engine::cleanup() {
  glfwTerminate();
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  std::cout << "Engine cleaned up.\n";
  return 0;
}

//> Helper functions
void Engine::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void Engine::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  (void)window;
  glViewport(0, 0, width, height);
}

std::string Engine::loadShaderSource(const std::string &shaderPath) {
  std::ifstream file(shaderPath);
  if (!file.is_open()) {
    std::cout << "Could not open shader at: " << shaderPath << std::endl;
    return ""; // Or throw an error
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

void Engine::compileShader(unsigned int shader, const char *shaderSource) {
  glShaderSource(shader, 1, &shaderSource, nullptr);
  glCompileShader(shader);

  // See if compilation was successfull
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
}
//< Helper functions
