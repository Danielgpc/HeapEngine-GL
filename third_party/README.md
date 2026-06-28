# Third-party folder

This directory is reserved for external dependencies or vendored libraries used by the project. 

Below is a list of the libraries included in this directory, along with their primary purpose in the project:

| Library   | Description                             | Purpose                                                                                  |
|:--------- |:--------------------------------------- |:---------------------------------------------------------------------------------------- |
| **GLAD**  | OpenGL Loading Library                  | Manages OpenGL function pointers so we can use modern OpenGL functions.                  |
| **GLFW**  | Graphics Library Framework              | Handles window creation, context management, and user input (keyboard/mouse).            |
| **GLM**   | OpenGL Mathematics                      | A header-only C++ math library tailored for graphics (vectors, matrices, transforms).    |
| **imgui** | Dear ImGui                              | A bloat-free, immediate-mode graphical user interface library for debugging and tooling. |
| **stb**   | stb single-file public domain libraries | Single-header libraries used primarily for image loading (`stb_image.h`) and writing.    |

## Directory Structure

To keep this folder maintainable, ensure libraries are organized by their respective folders or headers:

```text
third_party/
├── glad/
│   ├── include/
│   │   └── glad/
│   │       └── glad.h
│   └── src/
│       └── glad.c
├── glfw/
│   ├── include/
│   │   └── GLFW/
│   │       ├── glfw3.h
│   │       └── glfw3native.h
│   └── src/
│       └── [glfw source files]
├── glm/
│   └── glm/
│       ├── glm.hpp
│       └── [core headers & detail/ folders]
├── imgui/
│   ├── backends/
│   │   ├── imgui_impl_glfw/opengl.h/cpp
│   ├── imconfig.h
│   ├── imgui.cpp
│   ├── imgui.h
│   ├── imgui_*.cpp
└── stb/
    └── stb_image.h
```

This directory is reserved for external dependencies or vendored libraries used by the project.
