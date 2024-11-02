#include "vertex_buffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
  // generates a buffer
  glGenBuffers(1, &renderer_id);
  // select the buffer as the current one
  glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
  // set the size and location of the data,
  // also give to openGL a hint on how is going
  // to be the i/o of this buffer
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &renderer_id);
};

void VertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
};

void VertexBuffer::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
};
