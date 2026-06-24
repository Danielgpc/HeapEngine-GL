#include "window.h"
#include "logger.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

bool WindowManager::init(int width, int height, const char *title) {
  // 1. Initialize the underlying windowing library (GLFW)
  if (!glfwInit()) {
    Logger::log(LogLevel::ERROR, "Failed to initialize GLFW");
    return false;
  }

  // 2. Set up target OpenGL profile attributes (Core Profile 3.3)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // 3. Allocate OS-level window resource
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (window == nullptr) {
    Logger::log(LogLevel::ERROR, "Failed to create window");
    glfwTerminate();
    return false;
  }

  // 4. Make this window's OpenGL context current on the calling thread
  glfwMakeContextCurrent(window);
  // glfwSwapInterval(0); // 0 turns off V-Sync, unlocking the frame rate

  // 5. Load function pointers for modern OpenGL using GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::log(LogLevel::ERROR, "Failed to initialize GLAD");
    return false;
  }

  // 6. Register a static callback to adjust viewport dimensions when window
  // resizes
  glfwSetFramebufferSizeCallback(window,
                                 WindowManager::framebuffer_size_callback);
  glViewport(0, 0, width, height);

  // 7. Initialize ImGui bindings specifically linked to this window and OpenGL
  // version
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

void WindowManager::processInput() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void WindowManager::shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  if (window) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();
}

void WindowManager::framebuffer_size_callback(GLFWwindow *window, int width,
                                              int height) {
  (void)window;
  glViewport(0, 0, width, height);
}
