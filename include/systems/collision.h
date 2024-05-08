#pragma once
#include "components/collider.h"
#include "components/transform.h"
#include "ecs.h"
#include "events/collision.h"
#include "events/event_bus.h"

class CollisionSystem : public System {
  public:
    CollisionSystem() {
      RequireComponent<BoxCollider>();
      RequireComponent<Transform>();
    };
    void Update(std::unique_ptr<EventBus> &event_bus) {
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
            event_bus->Emit<CollisionEvent>(entity, entity_b);
          }
        };
      };
    };

  private:
    bool is_intercepting() {
      return false;
    }
};
