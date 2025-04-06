#include "index_buffer.h"
#include <glad/glad.h>

IndexBuffer::IndexBuffer(const void *data, unsigned int count) {
  this->count = count;
  glGenBuffers(1, &renderer_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
  // this count works over indices not vertices
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &renderer_id);
};

void IndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
};

void IndexBuffer::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};
