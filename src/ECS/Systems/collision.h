#pragma once
#include "ECS/Components/collider.h"
#include "ECS/Components/transform.h"
#include "ECS/Events/event_bus.h"
#include "ECS/Events/types/collision.h"
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
        auto &collider = entity.GetComponent<BoxCollider>();

        for (auto j = i; j != entities.end(); j++) {
          Entity entity_b = *j;

          if (entity == entity_b) {
            continue;
          }

          const auto &transform_b = entity_b.GetComponent<Transform>();
          auto &collider_b = entity_b.GetComponent<BoxCollider>();

          bool is_intercepting = AABB(transform.position, transform_b.position, collider, collider_b);
          collider.is_colliding = collider_b.is_colliding = is_intercepting;
          if (is_intercepting) {
            event_bus->Emit<CollisionEvent>(entity, entity_b);
          }
        };
      };
    };

  private:
    bool AABB(vec2 position_a, vec2 position_b, const BoxCollider &collider_a, const BoxCollider &collider_b) {
      return (position_a.x < position_b.x + collider_b.w && position_a.x + collider_a.w > position_b.x &&
              position_a.y < position_b.y + collider_b.h && position_a.y + collider_a.h > position_b.y);
    }
};
