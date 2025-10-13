#pragma once

#include "ECS/Components/sprite.h"
#include "Graphics/index_buffer.h"
#include "Graphics/shader.h"
#include "Graphics/vertex_array.h"
#include "Graphics/vertex_buffer.h"

class SpriteRenderer {
  private:
    VertexBuffer m_Vbo;
    VertexArray m_Vao;
    IndexBuffer m_Ebo;
    Shader m_Shader;
    // static constexpr float quad[] = {
    //     // Position | Texture coordinates
    //     -1.0f, -1.0f, 0.0f, 0.0f, // bottom left
    //     1.0f,  -1.0f, 1.0f, 0.0f, // bottom right
    //     -1.0f, 1.0f,  0.0f, 1.0f, // top left
    //     1.0f,  1.0f,  1.0f, 1.0f, // top right
    // };
    static constexpr unsigned int m_Indeces[] = {0, 1, 3, 0, 2, 3};
    static const glm::mat4 m_Projection;
    static const glm::mat4 view;

  public:
    SpriteRenderer(unsigned int quads = 1);
    ~SpriteRenderer() = default;
    void render(const class Texture *texture, const Sprite &sprite, const glm::vec2 &position) const;
    void batch_render(const std::vector<std::pair<const Texture *, glm::vec2>> &sprites);
};
