#pragma once
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
  private:
    unsigned int renderer_id;

  public:
    VertexArray();
    ~VertexArray();

    void AddLayout(VertexBuffer &vbo, VertexBufferLayout &layout) const;
    void Bind() const;
    void Unbind() const;
};
