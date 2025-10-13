#pragma once
#include "AssetStore/asset_store.h"

#include "ECS/Components/sprite.h"
#include "ECS/Components/transform.h"
#include "ECS/ecs.h"

#include "Graphics/sprite_renderer.h"
#include <memory>

class RenderSystem : public System {
  public:
    RenderSystem() {
      RequireComponent<Sprite>();
      RequireComponent<Transform>();
    }

    void Update(std::shared_ptr<SpriteRenderer> &renderer, std::shared_ptr<Store> &store) const {
      for (auto entity : GetEntities()) {
        const auto &sprite = entity.GetComponent<Sprite>();
        const auto &position = entity.GetComponent<Transform>().position;

        const Texture *texture = store->GetTexture(sprite.id);

        if (!texture) {
          Logger::err("texture not found: " + sprite.id);
        }

        renderer->render(texture, sprite, position);
      }
    }

    void BatchUpdate(std::shared_ptr<SpriteRenderer> &renderer, std::shared_ptr<Store> &store) const {
      auto entities = GetEntities();
      std::vector<std::pair<const Texture *, glm::vec2>> pairs;

      std::transform(entities.begin(), entities.end(), std::back_inserter(pairs), [store](Entity entity) {
        const auto &sprite = entity.GetComponent<Sprite>();
        const auto &position = entity.GetComponent<Transform>().position;

        return std::make_pair(            //
            store->GetTexture(sprite.id), //
            position + (glm::vec2((sprite.w / 2.0f) * sprite.scale.x, (sprite.h / 2.0f) * sprite.scale.y)));
      });

      renderer->batch_render(pairs);
    }
};
