#include "engine.h"
#include "defines.h"
#include "logger.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window.h"

int Engine::init() {
  Logger::init();

  // Delegation: Engine asks WindowManager to prepare a display canvas
  if (!windowManager.init(WIDTH, HEIGHT, "Heap engine gl window")) {
    return -1;
  }

  // Delegation: Engine tells Shader object to parse and build the pipeline
  if (!shader.init()) {
    return -1;
  }

  // Delegation: Engine loads local triangle vertices directly into hardware
  // VRAM
  mesh.init();

  Logger::log(LogLevel::INFO, "Engine initialized");
  return 0;
}

int Engine::run() {
  // Extract handle to run window lifecycle checking loop
  GLFWwindow *window = windowManager.getGLFWWindow();

  texture = image.loadImage("assets/container.jpg");

  while (!glfwWindowShouldClose(window)) {
    windowManager.processInput(); // Check for key bindings (e.g. ESC key)
    render();                     // Draw current scene graphics
    glfwSwapBuffers(
        window); // Swap front & back display buffers (avoids screen tearing)
    glfwPollEvents(); // Handle window messages, resizing, OS interruptions
  }

  return 0;
}

void Engine::render() {
  // --- FPS Calculations ---
  static double lastTime = glfwGetTime();
  static int frameCount = 0;
  static float fps = 0.0f;
  static float frameTimeMs = 0.0f;

  double currentTime = glfwGetTime();
  frameCount++;

  if (currentTime - lastTime >= 0.5) {
    fps = static_cast<float>(frameCount) /
          static_cast<float>(currentTime - lastTime);
    frameTimeMs = 1000.0f / fps;
    frameCount = 0;
    lastTime = currentTime;
  }
  // -------------------------

  // Clean back-buffer frame canvas color bits
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Bind the texture
  glBindTexture(GL_TEXTURE_2D, texture);

  // Use the separated components together safely to draw graphics
  shader.use(); // 1. Set global GPU program state
  mesh.draw();  // 2. Feed geometry primitives through program state

  // Render UI overlays via ImGui modules
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Performance");
  ImGui::Text("Application Average: %.1f FPS", fps);
  ImGui::Text("Frame Time: %.3f ms", frameTimeMs);
  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int Engine::cleanup() {
  mesh.cleanup();
  shader.cleanup();
  windowManager.shutdown();

  Logger::log(LogLevel::INFO, "Engine cleanup");
  return 0;
}
