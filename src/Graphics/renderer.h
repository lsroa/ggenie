#pragma once
#include "GLFW/glfw3.h"
#include "index_buffer.h"
#include "shader.h"
#include "vertex_array.h"

class Renderer {
  public:
    Renderer() = default;
    ~Renderer() = default;
    GLFWwindow *window;
    void Init();
    void Run();

  private:
    void render(VertexArray &vao, IndexBuffer &ebo);
};

void renderTexture(const class Texture &texture, const Shader &shader, const glm::vec2 &position);
