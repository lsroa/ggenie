#include "sprite_renderer.h"

#include "Graphics/index_buffer.h"
#include "Graphics/texture.h"
#include "Utils/logger.h"

#include <glm/ext/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer() : m_Shader(Shader({"./assets/shaders/color.frag", "./assets/shaders/default.vert"})) {
  VertexBuffer vbo(quad, sizeof(quad));
  IndexBuffer ebo(indices, sizeof(indices));
  VertexBufferLayout layout;

  layout.AddAttribute<float>("position", 2);
  layout.AddAttribute<float>("texture", 2);

  VertexArray vao;
  vao.AddLayout(vbo, layout);

  this->m_Vao = vao;
};

void SpriteRenderer::render(const Texture *texture, const glm::vec2 &position) const {
  if (texture == nullptr) {
    Logger::err("Texture not found");
    return;
  }
  texture->Bind(0);
  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(position, 0));
  model = glm::scale(model, glm::vec3(texture->width, texture->height, 0));
  m_Shader.SetMat4("model", model);
}
