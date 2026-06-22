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
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();

  ImGui::NewFrame();

  ImGui::ShowDemoWindow();

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
