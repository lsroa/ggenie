#pragma once

class VertexBuffer {
  private:
    unsigned int renderer_id;
    /* unsigned int count; */

  public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind();
};
