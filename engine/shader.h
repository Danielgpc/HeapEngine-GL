#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
public:
  bool init();
  void use() const;
  void cleanup();

private:
  unsigned int shaderProgram = 0;
  std::string loadShaderSource(const std::string &shaderPath);
  void compileShader(unsigned int shader, const char *shaderSource);
};