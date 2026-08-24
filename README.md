# HeapEngine-GL

**HeapEngine-GL** is a lightweight, from-scratch C++ OpenGL 4.x game engine (currently targeting 3.3 core for broad compatibility) built by a 14-year-old solo dev. The goal is a clean, modular foundation for a large-scale low-poly 3D open-world game (GTA 5 / RDR 2) with Far Cry 3 inspired/CS:S graphics.

### Current Features

- GLFW + GLAD windowing and OpenGL context management
- Custom Shader class with file loading and uniform helpers
- Mesh class with VBO/VAO/EBO support (textured quad example)
- Texture loading via STB (ImageHandler) with mipmaps
- Multi-texture blending (container + awesomeface classic)
- ImGui integration for runtime performance overlay (FPS, frame time)
- Clean engine/game separation via Application interface
- Logging system with colors and timestamps
- Makefile-based build system with static libs

**Current demo**: Renders a textured quad with color + UV attributes, blending two textures, and live performance stats.

### Project Structure (current)

text

```
HeapEngine-GL/
├── engine/
│   ├── src/           # Engine sources (.cc)
│   ├── *.h            # Engine headers (Application interface, Shader, Mesh...)
│   └── third_party/   # GLAD, GLFW, GLM, ImGui (docking), stb_image
├── game/
│   └── src/           # SandboxGame + main.cc
├── shaders/           # GLSL shaders
├── assets/            # Textures (container.jpg, awesomeface.png)
├── build/             # Build output (objects, libs, executable)
├── Makefile           # Top-level: delegates to engine/ and game/
├── TODO.md
└── README.md
```

### Build & Run

Bash

```
make all      # Build engine + game
make run      # Build and execute
make clean
```

The executable lands in build/game/voidscan.
