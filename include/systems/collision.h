#pragma once
#include "components/collider.h"
#include "components/transform.h"
#include "ecs.h"

class CollisionSystem : public System {
  public:
    CollisionSystem() {
      RequireComponent<BoxCollider>();
      RequireComponent<Transform>();
    };
    void Update() {
      auto entities = GetEntities();

      for (auto i = entities.begin(); i != entities.end(); i++) {
        Entity entity = *i;

        /* const auto &transform = entity.GetComponent<Transform>(); */
        /* const auto &collider = entity.GetComponent<BoxCollider>(); */

        for (auto j = i; j != entities.end(); j++) {
          Entity entity_b = *j;

          if (entity == entity_b) {
            continue;
          }

          /* const auto &transform_b = entity.GetComponent<Transform>(); */
          /* const auto &collider_b = entity.GetComponent<BoxCollider>(); */

          if (is_intercepting()) {
            Logger::log("colliding entity " + std::to_string(entity.GetId()) +
                        " with entity " + std::to_string(entity_b.GetId()));
          }
        };
      };
    };

  private:
    bool is_intercepting() {
      return false;
    }
};
