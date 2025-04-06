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

    void Update(std::shared_ptr<SpriteRenderer> renderer, std::shared_ptr<Store> &store) const {
      for (auto entity : GetEntities()) {
        const auto &sprite = entity.GetComponent<Sprite>();
        const auto &position = entity.GetComponent<Transform>().position;

        const Texture *texture = store->GetTexture(sprite.id);

        if (!texture) {
          Logger::err("texture not found: " + sprite.id);
        }

        renderer->render(texture, glm::vec2(position.x, position.y));
      }
    }
};
