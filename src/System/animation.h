#pragma once
#include "../Components/animation.h"
#include "../Components/sprite.h"
#include "../ECS/ecs.h"
/* #include "SDL2/SDL_timer.h" */

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

        animation.current_frame = (SDL_GetTicks() - animation.start_time) *
                                  animation.speed / 1000 %
                                  animation.total_frames;

        sprite.x = animation.current_frame * sprite.w;
      }
    }
};
