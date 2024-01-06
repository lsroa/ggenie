#pragma once
#include "asset_store.h"
#include "components/sprite.h"
#include "components/transform.h"
#include "ecs.h"

#include <SDL2/SDL_render.h>
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
        double rotation = entity.GetComponent<Transform>().rotation;

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
        SDL_Point center = {sprite.x + (sprite.w / 2),
                            sprite.y + (sprite.h / 2)};

        SDL_RendererFlip flip =
            sprite.is_flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        SDL_RenderCopyEx(renderer, texture, &srcRect, &target, rotation,
                         &center, flip);
      }
    }
};
