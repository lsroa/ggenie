#pragma once

#include "ECS/Components/sprite.h"
#include "Graphics/index_buffer.h"
#include "Graphics/shader.h"
#include "Graphics/vertex_array.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

class SpriteRenderer {
  private:
    VertexBuffer m_Vbo;
    VertexArray m_Vao;
    IndexBuffer m_Ebo;
    Shader m_Shader;
    static constexpr float quad[] = {
        // Position | Texture coordinates
        -1.0f, -1.0f, 0.0f, 0.0f, // bottom left
        1.0f,  -1.0f, 1.0f, 0.0f, // bottom right
        -1.0f, 1.0f,  0.0f, 1.0f, // top left
        1.0f,  1.0f,  1.0f, 1.0f, // top right
    };
    static constexpr unsigned int indices[] = {0, 1, 3, 0, 2, 3};
    static const glm::mat4 projection;
    static const glm::mat4 view;

  public:
    SpriteRenderer();
    ~SpriteRenderer() = default;
    void render(const class Texture *texture, const Sprite &sprite, const glm::vec2 &position) const;
};
