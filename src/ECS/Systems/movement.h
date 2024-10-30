#pragma once
#include "ECS/Components/rigid_body.h"
#include "ECS/Components/transform.h"
#include "ECS/ecs.h"

#include <glm/glm.hpp>

class MovementSystem : public System {
  public:
    MovementSystem() {
      RequireComponent<Transform>();
      RequireComponent<RigidBody>();
    };
    void Update(double delta_time) {
      for (auto entity : GetEntities()) {
        auto &transform = entity.GetComponent<Transform>();
        const auto [velocity] = entity.GetComponent<RigidBody>();

        transform.position += velocity * static_cast<float>(delta_time);
        /* Logger::log("Moving entity: " + std::to_string(entity.GetId()) + */
        /*             " x: " + std::to_string(transform.position.x) + */
        /*             " y: " + std::to_string(transform.position.y)); */
      }
    }
};
