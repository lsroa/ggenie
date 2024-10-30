#pragma once
#include "ECS/Components/animation.h"
#include "ECS/Components/sprite.h"
#include "ECS/ecs.h"

#include <SDL2/SDL_timer.h>

class AnimationSystem : public System {
  public:
    AnimationSystem() {
      RequireComponent<Animation>();
      RequireComponent<Sprite>();
    }

    void Update() {
      for (const auto &entity : GetEntities()) {
        auto &sprite = entity.GetComponent<Sprite>();
        auto &animation = entity.GetComponent<Animation>();

        if (!animation.is_loop && animation.current_frame == animation.total_frames - 1) {
          continue;
        }

        animation.current_frame =
            (SDL_GetTicks() - animation.start_time) * animation.speed / 1000 % animation.total_frames;

        sprite.x = animation.current_frame * sprite.w;
      }
    }
};
