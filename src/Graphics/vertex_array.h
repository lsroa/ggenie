#pragma once
#include "glad/glad.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
  private:
    unsigned int renderer_id;

  public:
    VertexArray();
    ~VertexArray();

    void AddLayout(VertexBuffer &vbo, VertexBufferLayout &layout) const {
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

    void Bind() const;
    void Unbind();
};
