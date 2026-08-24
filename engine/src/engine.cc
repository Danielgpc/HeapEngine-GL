#include "engine.h"
#include "defines.h"
#include "logger.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int Engine::init() {
  Logger::init();

  if (!windowManager.init(WIDTH, HEIGHT, "Heap engine gl window")) {
    return -1;
  }

  Logger::log(LogLevel::INFO, "Engine core initialized");
  return 0;
}

int Engine::run(Application *app) {
  GLFWwindow *window = windowManager.getGLFWWindow();

  app->onInit();

  // --- Core Performance Timing Variables ---
  double lastTime = glfwGetTime();
  double fpsLastTime = glfwGetTime();
  int frameCount = 0;
  float currentFps = 0.0f;
  float currentFrameTimeMs = 0.0f;

  while (!glfwWindowShouldClose(window)) {
    // Calculate Delta Timing
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    // --- Active FPS Calculations ---
    frameCount++;
    if (currentTime - fpsLastTime >= 0.5) {
      currentFps = static_cast<float>(frameCount) /
                   static_cast<float>(currentTime - fpsLastTime);
      currentFrameTimeMs = 1000.0f / currentFps;
      frameCount = 0;
      fpsLastTime = currentTime;
    }

    // Process window inputs
    windowManager.processInput();
    app->onUpdate(deltaTime);

    // Render clear operations
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Initialize ImGui frame targets
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
      ImGuiViewport *viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(viewport->WorkPos);
      ImGui::SetNextWindowSize(viewport->WorkSize);
      ImGui::SetNextWindowViewport(viewport->ID);

      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

      ImGuiWindowFlags dockspace_flags =
          ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
          ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
          ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
          ImGuiWindowFlags_NoBackground;

      ImGui::Begin("MainDockspaceWindow", nullptr, dockspace_flags);

      ImGuiID dockspace_id = ImGui::GetID("MainDockspace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f),
                       ImGuiDockNodeFlags_PassthruCentralNode);

      ImGui::End();

      ImGui::PopStyleVar(3);
    }

    // Your game rendering
    app->onRender(currentFps, currentFrameTimeMs);

    // Pass calculated performance indicators to the game view render layer
    app->onRender(currentFps, currentFrameTimeMs);

    // Finalize ImGui pipeline rendering layout
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  app->onShutdown();
  return 0;
}

int Engine::cleanup() {
  windowManager.shutdown();
  Logger::log(LogLevel::INFO, "Engine core cleanup");
  return 0;
}
