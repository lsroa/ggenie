#pragma once
#include "glm/glm.hpp"
#include <string>

struct Sprite {
    std::string id;
    glm::vec2 scale;
    int w, h;

    Sprite(const std::string &id = "", int w = 0, int h = 0,
           glm::vec2 scale = glm::vec2(1.0, 1.0)) {
      this->w = w;
      this->h = h;
      this->id = id;
      this->scale = scale;
    }
};
