#include "vertex_array.h"
#include "Utils/logger.h"

#include <glad/glad.h>

VertexArray::VertexArray() {
  glGenVertexArrays(1, &renderer_id);
};

void VertexArray::Bind() const {
  glBindVertexArray(this->renderer_id);
}

void VertexArray::Unbind() {
  glBindVertexArray(0);
}

VertexArray::~VertexArray() {
  glBindVertexArray(0);
}

void VertexArray::AddLayout(VertexBuffer &vbo, VertexBufferLayout &layout) const {
  Logger::info("Add layout");
  vbo.Bind();
  this->Bind();

  for (int i = 0; i < layout.GetAttributes().size(); i++) {
    const auto &attribute = layout.GetAttributes()[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(
        // Attribute index
        i,
        // the total size of the attribute
        attribute.count,
        // the type that holds
        attribute.type,
        // is not normalized
        GL_FALSE,
        // offset for the next row
        layout.stride,
        // offset within the row for the attribute
        reinterpret_cast<void *>(attribute.offset));
  }
}
