#include "vertex_buffer_layout.h"
#include "glad/glad.h"

template <>
void VertexBufferLayout::AddAttribute<float>(const char *name, unsigned int count) {
  this->attributes.push_back({.name = name, .type = GL_FLOAT, .count = count, .offset = this->stride});
  this->stride += sizeof(float) * count;
};
