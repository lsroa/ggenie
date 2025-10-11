#include "vertex_array.h"
#include "Graphics/vertex.h"
#include "Utils/logger.h"
#include "glm/ext/vector_float2.hpp"

#include <cstddef>
#include <glad/glad.h>

VertexArray::VertexArray() {
  glGenVertexArrays(1, &renderer_id);
};

void VertexArray::Bind() const {
  glBindVertexArray(this->renderer_id);
}

void VertexArray::Unbind() const {
  glBindVertexArray(0);
}

VertexArray::~VertexArray() {
  glBindVertexArray(0);
}

template <>
void VertexArray::AddLayout<Vertex>() const {
  Logger::info("Add layout for Vertex");
  this->Bind();

  // Position
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
      // Attribute index
      0,
      // the total size of the attribute
      2,
      // the type that holds
      GL_FLOAT,
      // is not normalized
      GL_FALSE,
      // offset for the next row
      sizeof(Vertex),
      // offset within the row for the attribute
      (void *)(offsetof(Vertex, position)));

  // Texture Coordinates
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
      // Attribute index
      1,
      // the total size of the attribute
      2,
      // the type that holds
      GL_FLOAT,
      // is not normalized
      GL_FALSE,
      // offset for the next row
      sizeof(Vertex),
      // offset within the row for the attribute
      (void *)(offsetof(Vertex, text_coord)));
}
