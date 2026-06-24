#include "shader.h"
#include "logger.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool Shader::init() {
  std::string source = loadShaderSource("shaders/shader.vert");
  const char *vertexShaderSource = source.c_str();
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  compileShader(vertexShader, vertexShaderSource);

  source = loadShaderSource("shaders/shader.frag");
  const char *fragmentShaderSource = source.c_str();
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  compileShader(fragmentShader, fragmentShaderSource);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success = 0;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    Logger::log(LogLevel::ERROR, "Failed to create shader program");
    std::cout << infoLog << std::endl;
    return false;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return true;
}

void Shader::use() const {
  glUseProgram(shaderProgram);
}

void Shader::cleanup() {
  if (shaderProgram != 0) {
    glDeleteProgram(shaderProgram);
  }
}

std::string Shader::loadShaderSource(const std::string &shaderPath) {
  std::ifstream file(shaderPath);
  if (!file.is_open()) {
    Logger::log(LogLevel::WARN, "Could not open shader at ", shaderPath);
    return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

void Shader::compileShader(unsigned int shader, const char *shaderSource) {
  glShaderSource(shader, 1, &shaderSource, nullptr);
  glCompileShader(shader);

  int success = 0;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    Logger::log(LogLevel::ERROR, "Could not compile shader");
    std::cout << infoLog << std::endl;
  }
}