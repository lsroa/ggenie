#pragma once
#include "../src/AssetStore/asset_store.h"
#include "../src/Components/sprite.h"
#include "../src/Components/transform.h"
#include "../src/ECS/ecs.h"
#include "SDL2/SDL_render.h"
#include <SDL_rect.h>

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
            sprite.w * static_cast<int>(sprite.scale.x),
            sprite.h * static_cast<int>(sprite.scale.y),
        };

        auto texture = store->GetTexture(sprite.id);

        if (!texture) {
          Logger::err("texture not found: " + sprite.id);
        }

        // the crop box for the image usually 0,0 for the complete image
        SDL_Rect srcRect = {sprite.x, sprite.y, sprite.w, sprite.h};

        SDL_RenderCopy(renderer, texture, &srcRect, &target);
      }
    }
};