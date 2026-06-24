#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager {
public:
  bool init(int width, int height, const char* title);
  void processInput();
  void shutdown();
  
  // Inline getter in window.h exposes the pointer safely to the Engine loop
  // without exposing internal mutability recklessly.
  GLFWwindow* getGLFWWindow() const { return window; }

private:
  GLFWwindow *window = nullptr;
  static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};