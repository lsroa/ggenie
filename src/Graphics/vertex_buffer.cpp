#include "vertex_buffer.h"
#include "vertex.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(unsigned int size) {
  // generates a buffer
  glGenBuffers(1, &m_RendererId);
  // select the buffer as the current one
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
  // allocate the max size and location of the data,
  // also give to openGL a hint on how is going
  // to be the i/o of this buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &m_RendererId);
};

void VertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
};

void VertexBuffer::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
};
