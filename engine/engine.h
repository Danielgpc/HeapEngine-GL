#pragma once

#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "image.h"

class Engine {
public:
  int init();
  int run();
  int cleanup();

private:
  // --- Composition: Engine owns instances of specialized classes ---
  WindowManager
      windowManager; // Handles GLFW context, window creation, and input
  Shader shader;     // Handles reading, compiling, and linking GLSL shaders
  Mesh mesh; // Handles Vertex Buffer Objects (VBO) and Vertex Arrays (VAO)
  ImageHandler image; // Handles image loading

  unsigned int texture;

  void render();
};
