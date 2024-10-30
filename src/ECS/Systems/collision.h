#pragma once
#include "ECS/Components/collider.h"
#include "ECS/Components/transform.h"
#include "ECS/Events/collision.h"
#include "ECS/Events/event_bus.h"
#include "ECS/ecs.h"

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

        const auto &transform = entity.GetComponent<Transform>();
        const auto &collider = entity.GetComponent<BoxCollider>();

        for (auto j = i; j != entities.end(); j++) {
          Entity entity_b = *j;

          if (entity == entity_b) {
            continue;
          }

          const auto &transform_b = entity.GetComponent<Transform>();
          const auto &collider_b = entity.GetComponent<BoxCollider>();
          if (is_intercepting(transform.position, transform_b.position, vec2(collider.w, collider.h),
                              vec2(collider_b.w, collider_b.h))) {
            event_bus->Emit<CollisionEvent>(entity, entity_b);
          }
        };
      };
    };

  private:
    bool is_intercepting(vec2 position_a, vec2 position_b, vec2 collider_a, vec2 collider_b) {
      return (position_a.x + collider_a.x > position_b.x) && (position_a.y < position_b.y + collider_b.y) &&
             (position_b.y < position_a.y + collider_a.y) && (position_a.x < position_b.x + collider_b.x);
    }
};
