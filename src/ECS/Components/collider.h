#pragma once
#include "glm/ext/vector_float2.hpp"

struct BoxCollider {
    glm::vec2 offset;
    int w, h;

    BoxCollider(int w = 0, int h = 0, glm::vec2 offset = glm::vec2(0)) {
      this->h = h;
      this->w = w;
      this->offset = offset;
    }
};

struct CircleCollider {
    glm::vec2 offset;
    int r;

    CircleCollider(int r = 1, glm::vec2 offset = glm::vec2(0)) {
      this->r = r;
      this->offset = offset;
    }
};
