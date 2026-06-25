#pragma once

// The interface that any user game will implement
class Application {
public:
    virtual ~Application() = default;

    // Called once when the application starts
    virtual void onInit() = 0;

    // Called every frame to update game logic
    virtual void onUpdate(float deltaTime) = 0;

    // Called every frame to issue draw calls and ImGui UI layouts
    virtual void onRender(float fps, float frameTimeMs) = 0;

    // Called before the application closes
    virtual void onShutdown() = 0;
};