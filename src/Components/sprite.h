#pragma once
#include "glm/ext/vector_float2.hpp"
#include <string>

struct Sprite {
    std::string id;
    glm::vec2 scale;
    int w, h, x, y;

    Sprite(const std::string &id = "", int x = 0, int y = 0, int w = 0,
           int h = 0, glm::vec2 scale = glm::vec2(1.0, 1.0)) {
      this->x = x;
      this->y = y;
      this->w = w;
      this->h = h;
      this->id = id;
      this->scale = scale;
    }
};
