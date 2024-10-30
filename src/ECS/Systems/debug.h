#pragma once
#include "ECS/Components/collider.h"
#include "ECS/Components/transform.h"
#include "ECS/Events/collision.h"
#include "ECS/Events/event_bus.h"
#include "ECS/ecs.h"
#include <SDL_render.h>
#include <memory>

class DebugSystem : public System {
  public:
    std::vector<Entity> colliding_entities;
    DebugSystem() {
      RequireComponent<BoxCollider>();
      RequireComponent<Transform>();
    }

    void Update(SDL_Renderer *renderer) {
      for (const auto &entity : GetEntities()) {
        auto &collider = entity.GetComponent<BoxCollider>();
        auto &transform = entity.GetComponent<Transform>();

        SDL_Rect box = {static_cast<int>(transform.position.x + collider.offset.x),
                        static_cast<int>(transform.position.y + collider.offset.y), collider.w, collider.h};

        /* if (std::find(colliding_entities.begin(), colliding_entities.end(), entity) != colliding_entities.end()) { */
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        /* } else { */
        /*   SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); */
        /* } */
        SDL_RenderDrawRect(renderer, &box);
      }
    }

    void SubscribeToEvents(std::unique_ptr<EventBus> &event_bus) {
      event_bus->Subscribe<CollisionEvent, DebugSystem>(this, &DebugSystem::onCollision);
    }

  private:
    void onCollision(CollisionEvent &event) {
      Logger::log("Colliding entities");
      /* colliding_entities.push_back(event.a); */
      /* colliding_entities.push_back(event.b); */
    }
};
