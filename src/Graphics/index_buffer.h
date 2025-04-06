#pragma once

class IndexBuffer {
  private:
    unsigned int renderer_id;
    unsigned int count;

  public:
    IndexBuffer(const void *data, unsigned int size);
    ~IndexBuffer();
    void Bind() const;
    void Unbind();
};
