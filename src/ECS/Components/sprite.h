#pragma once
#include "glm/ext/vector_float2.hpp"
#include <string>

struct Sprite {
    // asset id
    std::string id;
    glm::vec2 scale;
    bool is_flipped;
    int w, h, x, y;

    Sprite(const std::string &id = "", int x = 0, int y = 0, int w = 0, int h = 0,
           glm::vec2 scale = glm::vec2(1.0, 1.0), bool is_flipped = false) {
      this->x = x;
      this->y = y;
      this->w = w;
      this->h = h;
      this->id = id;
      this->scale = scale;
      this->is_flipped = is_flipped;
    }
};
