#include "sprite_renderer.h"

#include "GLFW/glfw3.h"
#include "Game/game.h"
#include "Graphics/texture.h"
#include "Graphics/vertex.h"
#include "Utils/logger.h"
#include <OpenGL/gl.h>
#include <array>
#include <glad/glad.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#define GL_ERR_CHECK(label)                                                                                            \
  while (GLenum err = glGetError()) {                                                                                  \
    Logger::err(std::string(label) + " GL Error: " + std::to_string(err));                                             \
    assert(false);                                                                                                     \
  }

const glm::mat4 SpriteRenderer::m_Projection = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);
const glm::mat4 SpriteRenderer::view = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

SpriteRenderer::SpriteRenderer(unsigned int quads)
    : m_Vbo(quads * 4), m_Vao(), m_Ebo(m_Indeces, sizeof(m_Indeces)),
      m_Shader(Shader({"./assets/shaders/color.frag", "./assets/shaders/default.vert"})) {

  Logger::info("Sprite renderer spawn");

  this->m_Vao = VertexArray();
  GL_ERR_CHECK("Add VertexArray");

  this->m_Vao.AddLayout<Vertex>();
  GL_ERR_CHECK("Add layout");
};

std::array<Vertex, 4> CreateQuad() {
  return {
      Vertex{.position = glm::vec2(-1.0f, -1.0f), .text_coord = glm::vec2(0.0f, 0.0f)},
      Vertex{.position = glm::vec2(1.0f, -1.0f), .text_coord = glm::vec2(1.0f, 0.0f)},
      Vertex{.position = glm::vec2(-1.0f, 1.0f), .text_coord = glm::vec2(0.0f, 1.0f)},
      Vertex{.position = glm::vec2(1.0f, 1.0f), .text_coord = glm::vec2(1.0f, 1.0f)},
  };
};

void SpriteRenderer::batch_render(const std::vector<std::pair<const Texture *, glm::vec2>> &sprites) {
  Logger::info("batch rendering");
  for (const auto &pair : sprites) {
    auto [texture, position] = pair;
    std::cout << "Pair: -------------------------" << std::endl;
    std::cout << "\t Texture: " << *texture << std::endl;
    std::cout << std::format("\t Position: x:{} y:{}\n", position.x, position.y) << std::endl;
  }
}

void SpriteRenderer::render(const Texture *texture, const Sprite &sprite, const glm::vec2 &position) const {
  if (texture == nullptr) {
    Logger::err("Texture not found");
    return;
  }

  m_Vao.Bind();
  GL_ERR_CHECK("Bind vao");

  m_Shader.Bind();
  GL_ERR_CHECK("Bind shader");

  glm::mat4 model = glm::translate(
      glm::mat4(1.0f),
      glm::vec3(position + (glm::vec2((sprite.w / 2.0f) * sprite.scale.x, (sprite.h / 2.0f) * sprite.scale.y)), 0));

  model = glm::scale(model, glm::vec3((sprite.w / 2.0f) * sprite.scale.x, (sprite.h / 2.0f) * sprite.scale.y, 0));

  m_Shader.SetUniformi("texture_1", 0);
  GL_ERR_CHECK("Set uniform texture_1");

  m_Shader.SetMat4("model", model);
  GL_ERR_CHECK("Set uniform model");

  m_Shader.SetMat4("projection", this->m_Projection);
  GL_ERR_CHECK("Set uniform projection");

  m_Shader.SetMat4("view", this->view);
  GL_ERR_CHECK("Set uniform view");

  m_Shader.SetUniform1f("iTime", float(glfwGetTime()));
  GL_ERR_CHECK("Set uniform iTime");

  m_Shader.SetVec2("sprite_offset", glm::vec2(sprite.x, sprite.y));
  GL_ERR_CHECK("Set sprite offset uniform");

  m_Shader.SetVec2("sprite_size", glm::vec2(sprite.w, sprite.h));
  GL_ERR_CHECK("Set sprite size uniform");

  m_Shader.SetVec2("texture_size", glm::vec2(texture->width, texture->height));
  GL_ERR_CHECK("Set texture size");

  texture->Bind(0);
  GL_ERR_CHECK("Bind texture");

  m_Ebo.Bind();
  GL_ERR_CHECK("Bind ebo");

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  GL_ERR_CHECK("Draw elements");
}
