#pragma once
#include "../src/AssetStore/asset_store.h"
#include "../src/Components/sprite.h"
#include "../src/Components/transform.h"
#include "../src/ECS/ecs.h"
#include "SDL2/SDL_render.h"

class RenderSystem : public System {
  public:
    RenderSystem() {
      RequireComponent<Sprite>();
      RequireComponent<Transform>();
    }

    void Update(SDL_Renderer *renderer, std::shared_ptr<Store> &store) {
      for (auto entity : GetEntities()) {
        auto &sprite = entity.GetComponent<Sprite>();
        auto &position = entity.GetComponent<Transform>().position;

        SDL_Rect target = {
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            // this needs to be multiplied by the transform scale
            sprite.w,
            sprite.h,
        };

        auto texture = store->GetTexture(sprite.id);

        // the crop box for the image usually 0,0 for the complete image
        /* SDL_Rect srcRect = {0, 0, sprite.w, sprite.h}; */

        SDL_RenderCopy(renderer, texture, NULL, &target);
      }
    }
};
