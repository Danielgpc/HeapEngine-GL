#include "mesh.h"
#include "defines.h"

void Mesh::init() {
  // 1. Generate unique hardware identifiers for memory buffers
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  // 2. Bind VAO first: it acts as a wrapper wrapper that records attribute layouts
  glBindVertexArray(VAO);

  // 3. Bind and stream vertex array coordinates/colors from RAM to GPU VRAM
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // 4. Attribute Layout Definition:
  // Position Attribute (Location 0, 3 floats, starts at offset 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  
  // Color Attribute (Location 1, 3 floats, starts after 3 floats of position)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // 5. Unbind VAO to prevent accidental modifications elsewhere in the program
  glBindVertexArray(0);
}

void Mesh::draw() const {
  // Bind recorded configuration and trigger the OpenGL pipeline draw call
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Mesh::cleanup() {
  if (VBO != 0) glDeleteBuffers(1, &VBO);
  if (VAO != 0) glDeleteVertexArrays(1, &VAO);
}