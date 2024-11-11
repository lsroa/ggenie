#pragma once
#include "ECS/Components/collider.h"
#include "ECS/Components/transform.h"
#include "ECS/ecs.h"
#include <SDL_render.h>

class DebugSystem : public System {
  public:
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

        if (collider.is_colliding) {
          SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else {
          SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        SDL_RenderDrawRect(renderer, &box);
      }
    }
};
