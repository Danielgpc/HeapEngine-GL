#include "engine.h"
#include "application.h"
#include "shader.h"
#include "mesh.h"
#include "image.h"
#include "imgui.h"

class SandboxGame : public Application {
private:
  Shader shader;
  Mesh mesh;
  ImageHandler image;
  unsigned int texture1 = 0;
  unsigned int texture2 = 0;

public:
  SandboxGame() : shader("shaders/shader.vert", "shaders/shader.frag") {}

  void onInit() override {
    mesh.init();

    // Load textures
    texture1 = image.loadImage("assets/container.jpg", GL_RGB);
    texture2 = image.loadImage("assets/awesomeface.png", GL_RGBA);

    // Bind uniform slots
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
  }

  void onUpdate(float deltaTime) override {
    static float rotation = 0.0f;
    rotation += deltaTime * 60.0f; // Rotate speed

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotation),
                        glm::vec3(0.0f, 0.0f, 1.0f)); // Y axis spin
    // model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.5f)); // uncomment
    // to move it

    shader.use();
    shader.setMat4("transform", model);
  }

  void onRender(float fps, float frameTimeMs) override {
    // 1. Texture setups
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // 2. Main mesh drawing commands
    shader.use();
    mesh.draw();

    // 3. Performance tracking overlay display module
    ImGui::Begin("Performance");
    ImGui::Text("Application Average: %.1f FPS", fps);
    ImGui::Text("Frame Time: %.3f ms", frameTimeMs);
    ImGui::End();
  }

  void onShutdown() override {
    mesh.cleanup();
    shader.cleanup();
    if (texture1 != 0)
      glDeleteTextures(1, &texture1);
    if (texture2 != 0)
      glDeleteTextures(1, &texture2);
  }
};

int main() {
  Engine engine;

  if (engine.init() != 0) {
    return 1;
  }

  SandboxGame game;
  if (engine.run(&game) != 0) {
    return 2;
  }

  return engine.cleanup();
}
