#pragma once
#include "glm/glm.hpp"
#include <string>
using namespace glm;

struct Sprite {
    std::string id;
    int w, h;

    Sprite(const std::string &id = "", int w = 0, int h = 0) {
      this->w = w;
      this->h = h;
      this->id = id;
    }
};
