#include "engine.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "logger.h"

int Engine::init() {
  Logger::init();

  if (!initWindow()) {
    return -1;
  }

  if (!initShaders()) {
    return -1;
  }

  initMesh();

  Logger::log(LogLevel::INFO, "Engine initialized");
  return 0;
}

int Engine::run() {
  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    render();
    glfwSwapBuffers(window);
    glfwPollEvents();
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

  // Update FPS metrics every 0.5 seconds to make it readable
  if (currentTime - lastTime >= 0.5) {
    fps = static_cast<float>(frameCount) /
          static_cast<float>(currentTime - lastTime);
    frameTimeMs = 1000.0f / fps;

    frameCount = 0;
    lastTime = currentTime;
  }
  // -------------------------

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Custom Performance Overlay/Window
  ImGui::Begin("Performance");
  ImGui::Text("Application Average: %.1f FPS", fps);
  ImGui::Text("Frame Time: %.3f ms", frameTimeMs);
  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int Engine::cleanup() {
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteProgram(shaderProgram);

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  if (window) {
    glfwDestroyWindow(window);
  }

  glfwTerminate();

  Logger::log(LogLevel::INFO, "Engine cleanup");
  return 0;
}
