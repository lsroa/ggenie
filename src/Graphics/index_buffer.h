#pragma once

class IndexBuffer {
  private:
    unsigned int m_RendererId;
    unsigned int m_Count;

  public:
    IndexBuffer(const void *data, unsigned int size);
    ~IndexBuffer();
    void Bind() const;
    void Unbind();
};
