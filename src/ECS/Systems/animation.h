#pragma once
#include "ECS/Components/animation.h"
#include "ECS/Components/sprite.h"
#include "ECS/ecs.h"

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
            static_cast<int>((glfwGetTime() - animation.start_time) * 10 / animation.speed) % animation.total_frames;

        sprite.x = animation.current_frame * sprite.w;
      }
    }
};
