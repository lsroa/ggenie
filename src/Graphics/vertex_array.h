#pragma once

class VertexArray {
  private:
    unsigned int renderer_id;

  public:
    VertexArray();
    ~VertexArray();

    template <typename T>
    void AddLayout() const;
    void Bind() const;
    void Unbind() const;
};
