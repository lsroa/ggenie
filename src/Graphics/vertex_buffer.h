#pragma once

class VertexBuffer {
  private:
    unsigned int m_RendererId;

  public:
    VertexBuffer(unsigned int size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind();
};
