#include "engine.h"
#include "defines.h"
#include "logger.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

bool Engine::initWindow() {
  if (!glfwInit()) {
    Logger::log(LogLevel::ERROR, "Failed to initialize GLFW");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window = glfwCreateWindow(WIDTH, HEIGHT, "Heap engine gl window", nullptr,
                            nullptr);
  if (window == nullptr) {
    Logger::log(LogLevel::ERROR, "Failed to create window");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::log(LogLevel::ERROR, "Failed to initialize GLAD");
    return false;
  }

  glfwSetFramebufferSizeCallback(window, Engine::framebuffer_size_callback);
  glViewport(0, 0, WIDTH, HEIGHT);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
  return true;
}

void Engine::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void Engine::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  (void)window;
  glViewport(0, 0, width, height);
}
