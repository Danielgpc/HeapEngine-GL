#include "engine.h"
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
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int Engine::cleanup() {
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteProgram(shaderProgram);

  if (window) {
    glfwDestroyWindow(window);
  }

  glfwTerminate();
  Logger::log(LogLevel::INFO, "Engine cleanup");
  return 0;
}
