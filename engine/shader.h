#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
public:
  unsigned int ID;

  Shader(const char *vertexPath, const char *fragmentPath);

  void use() { glUseProgram(ID); }

  void setBool(const std::string &name, bool value) const;

  void setInt(const std::string &name, int value) const;

  void setFloat(const std::string &name, float value) const;

  void cleanup();

private:
  void checkCompileErrors(unsigned int shader, std::string type);
};
