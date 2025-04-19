#include "sprite_renderer.h"

#include "Graphics/texture.h"
#include "Utils/logger.h"
#include <glad/glad.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer()
    : m_Vbo(nullptr, 0), m_Ebo(nullptr, 0),
      m_Shader(Shader({"./assets/shaders/color.frag", "./assets/shaders/default.vert"})) {
  Logger::info("Sprite renderer spawn");
  this->m_Vbo = VertexBuffer(quad, sizeof(quad));
  this->m_Ebo = IndexBuffer(indices, sizeof(indices));
  VertexBufferLayout layout;

  layout.AddAttribute<float>("position", 2);
  layout.AddAttribute<float>("texture_coordinates", 2);

  this->m_Vao = VertexArray();
  this->m_Vao.AddLayout(m_Vbo, layout);
};

void SpriteRenderer::render(const Texture *texture, const glm::vec2 &position) const {
  glm::mat4 projection(1.0f);
  projection = glm::ortho(0.0f, (float)800, 0.0f, (float)600, -1.0f, 1.0f);

  m_Vao.Bind();
  m_Ebo.Bind();

  if (texture == nullptr) {
    Logger::err("Texture not found");
    return;
  }
  texture->Bind(0);
  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(position, 0));
  model = glm::scale(model, glm::vec3(texture->width, texture->height, 0));

  m_Shader.Bind();
  m_Shader.SetMat4("model", model);
  m_Shader.SetMat4("projection", projection);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
