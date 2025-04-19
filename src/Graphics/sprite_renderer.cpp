#include "sprite_renderer.h"

#include "GLFW/glfw3.h"
#include "Graphics/texture.h"
#include "Utils/logger.h"
#include <glad/glad.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#define GL_ERR_CHECK(label)                                                                                            \
  while (GLenum err = glGetError()) {                                                                                  \
    Logger::err(std::string(label) + " GL Error: " + std::to_string(err));                                             \
    assert(false);                                                                                                     \
  }

SpriteRenderer::SpriteRenderer()
    : m_Vbo(quad, sizeof(quad)), m_Vao(), m_Ebo(indices, sizeof(indices)),
      m_Shader(Shader({"./assets/shaders/color.frag", "./assets/shaders/default.vert"})) {
  Logger::info("Sprite renderer spawn");
  VertexBufferLayout layout;

  layout.AddAttribute<float>("position", 2);
  layout.AddAttribute<float>("texture_coordinates", 2);

  this->m_Vao = VertexArray();
  this->m_Vao.AddLayout(m_Vbo, layout);
};

void SpriteRenderer::render(const Texture *texture, const glm::vec2 &position) const {
  if (texture == nullptr) {
    Logger::err("Texture not found");
    return;
  }

  m_Vao.Bind();
  GL_ERR_CHECK("Bind vao");

  m_Shader.Bind();
  GL_ERR_CHECK("Bind shader");

  glm::mat4 projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(position, 0));
  model = glm::scale(model, glm::vec3(texture->width, texture->height, 0));

  m_Shader.SetUniformi("texture_1", 0);
  GL_ERR_CHECK("Set uniform texture_1");
  m_Shader.SetMat4("model", model);
  GL_ERR_CHECK("Set uniform model");
  m_Shader.SetMat4("projection", projection);
  GL_ERR_CHECK("Set uniform projection");
  m_Shader.SetMat4("view", view);
  GL_ERR_CHECK("Set uniform view");
  m_Shader.SetUniform1f("iTime", float(glfwGetTime()));
  GL_ERR_CHECK("Set uniform iTime");

  texture->Bind(0);
  GL_ERR_CHECK("Bind texture");

  m_Ebo.Bind();
  GL_ERR_CHECK("Bind ebo");

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  GL_ERR_CHECK("Draw elements");
}
