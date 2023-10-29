#pragma once
#include "glm/glm.hpp"
using namespace glm;

struct RigidBody {
    vec2 velocity;
    RigidBody(vec2 velocity = vec2(0.0, 0.0)) {
      this->velocity = velocity;
    }
};
