#pragma once
#include "glm/ext/vector_float2.hpp"

typedef glm::vec2 vec2;

struct Transform {
    vec2 position;
    vec2 scale;
    double rotation;

    Transform(vec2 position = vec2(0, 0), vec2 scale = vec2(1, 1),
              double rotation = 0) {
      this->position = position;
      this->scale = scale;
      this->rotation = rotation;
    }
};
