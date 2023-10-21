#pragma once
#include "glm/glm.hpp"

struct Transform {
  glm::vec2 pos;
  glm::vec2 vel;
  glm::mat2 rotation;
};
