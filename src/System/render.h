#pragma once
#include "../src/Components/sprite.h"
#include "../src/Components/transform.h"
#include "../src/ECS/ecs.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"

class RenderSystem : public System {
  public:
    RenderSystem() {
      RequireComponent<Sprite>();
      RequireComponent<Transform>();
    }

    void Update(SDL_Renderer *renderer) {
      for (auto entity : GetEntities()) {
        auto &render = entity.GetComponent<Sprite>();
        auto &position = entity.GetComponent<Transform>().position;

        SDL_Rect target = {
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            render.w,
            render.h,
        };

        SDL_RenderDrawRect(renderer, &target);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        SDL_RenderFillRect(renderer, &target);
      }
    }
};
