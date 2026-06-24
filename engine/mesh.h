#pragma once

#include <glad/glad.h>

class Mesh {
public:
  void init();
  void draw() const;
  void cleanup();

private:
  unsigned int VBO = 0;
  unsigned int VAO = 0;
  unsigned int EBO = 0;
};
