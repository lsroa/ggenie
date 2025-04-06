#pragma once
#include <vector>

struct Attribute {
    std::string name;
    unsigned int type;
    unsigned int count;
    unsigned int offset;
};

class VertexBufferLayout {
  private:
    std::vector<Attribute> attributes;

  public:
    unsigned int stride = 0;
    VertexBufferLayout() = default;
    ~VertexBufferLayout() = default;

    template <typename T>
    void AddAttribute(const char *name, unsigned int count) {};

    const std::vector<Attribute> &GetAttributes() const {
      return attributes;
    }

    template <>
    void AddAttribute<float>(const char *name, unsigned int count) {
      this->attributes.push_back({.name = name, .type = 5126, .count = count, .offset = this->stride});
      this->stride += sizeof(float) * count;
    }
};
