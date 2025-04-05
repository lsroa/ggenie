#pragma once

#include "Graphics/shader.h"
#include "Graphics/vertex_array.h"

class SpriteRenderer {
  private:
    VertexArray m_Vao;
    Shader m_Shader;
    static constexpr float quad[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, // bottom left
        1.0f,  -1.0f, 1.0f, 0.0f, // bottom right
        -1.0f, 1.0f,  0.0f, 1.0f, // top left
        1.0f,  1.0f,  1.0f, 1.0f, // top right
    };
    static constexpr unsigned int indices[] = {0, 1, 3, 0, 2, 3};

  public:
    SpriteRenderer();
    ~SpriteRenderer() = default;
    void render(const class Texture *texture, const glm::vec2 &position) const;
};
