#include "vertex_array.h"

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
