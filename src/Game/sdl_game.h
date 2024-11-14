#pragma once

#include "AssetStore/asset_store.h"

#include "ECS/Systems/animation.h"
#include "ECS/Systems/collision.h"
#include "ECS/Systems/debug.h"
#include "ECS/Systems/input.h"
#include "ECS/Systems/movement.h"
#include "ECS/Systems/render.h"

#include "Game/game.h"

#include <LDtkLoader/Project.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL_render.h>

class SDLGame : public Game {
  public:
    SDLGame();
    ~SDLGame();

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int ms = 0;
    std::shared_ptr<SDLStore> store;

  public:
    void Init() override {
      Logger::log("Game init");

      int result = SDL_Init(SDL_INIT_VIDEO);
      if (result != 0) {
        Logger::err("Error SDL init video");
        return;
      }

      SDL_DisplayMode displayMode;
      SDL_GetCurrentDisplayMode(0, &displayMode);
      this->width = 320 * SCALE;
      this->height = 192 * SCALE;

      window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height,
                                SDL_WINDOW_BORDERLESS);
      if (!window) {
        Logger::err("Error creating window");
        return;
      }

      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

      if (!renderer) {
        Logger::err("Renderer error");
        return;
      }

      state = State::running;
    }

    void Destroy() override {
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
    }
    void Update() override {
      int time = MPF - (SDL_GetTicks() - ms);
      if (time > 0) {
        SDL_Delay(time);
      }
      double delta = (SDL_GetTicks() - ms) / 1000.0f;
      ms = SDL_GetTicks();

      /* Clear events */
      event_bus->Reset();

      /* Register events */
      // NOTE: we could do this for common methods like update
      for (const auto &system_pair : registry->GetAllSystems()) {
        system_pair.second->SubscribeToEvents(event_bus);
      }

      /* Call the update of the systems */
      registry->GetSystem<CollisionSystem>().Update(event_bus);
      registry->GetSystem<MovementSystem>().Update(delta);
      registry->GetSystem<AnimationSystem>().Update();

      /* Add batched entities */
      registry->Update();
    }

    void Render() override {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      registry->GetSystem<RenderSystem>().Update(renderer, store);

      if (state == State::debug) {
        registry->GetSystem<DebugSystem>().Update(renderer);
      }

      /* swap back with front buffer */
      SDL_RenderPresent(renderer);
    }

    void LoadLevel(int levelId) override {
      Logger::info("Loading level " + std::to_string(levelId));

      /* Register systems */
      registry->AddSystem<MovementSystem>();
      registry->AddSystem<RenderSystem>();
      registry->AddSystem<AnimationSystem>();
      registry->AddSystem<CollisionSystem>();
      registry->AddSystem<DebugSystem>();
      registry->AddSystem<InputSystem>();

      store->AddTexture(renderer, "tilemap", "./assets/tilemap_1.png");
      store->AddTexture(renderer, "tank", "./assets/tank.png");

      /* Load ldtk */
      ldtk::Project ldtk_project;
      ldtk_project.loadFromFile("./assets/tank_wars.ldtk");

      const auto &world = ldtk_project.getWorld();

      const auto &level = world.getLevel(levelId);

      const auto &layers = level.allLayers();

      std::vector<std::string> layer_names;
      std::transform(layers.rbegin(), layers.rend(), std::back_inserter(layer_names),
                     [](const ldtk::Layer &l) { return l.getName(); });

      for (const auto &layer_id : layer_names) {

        const auto &layer = level.getLayer(layer_id);

        if (!layer.isVisible()) {
          continue;
        }

        const auto &tiles_vector = layer.allTiles();

        for (ldtk::Tile tile : tiles_vector) {
          auto tile_entity = registry->CreateEntity();
          auto [x, y] = tile.getPosition();
          auto [tx, ty, w, h] = tile.getTextureRect();
          tile_entity.AddComponent<Transform>(glm::vec2(x * SCALE, y * SCALE));
          tile_entity.AddComponent<Sprite>("tilemap", tx, ty, w, h, glm::vec2(SCALE));
        }
      }

      auto tank_1 = registry->CreateEntity();
      tank_1.AddComponent<Transform>(glm::vec2(1.0));
      tank_1.AddComponent<RigidBody>(glm::vec2(30.0, 0.0));
      tank_1.AddComponent<Sprite>("tank", 0, 16, 16, 16, glm::vec2(SCALE));
      tank_1.AddComponent<Animation>(2, 4);
      tank_1.AddComponent<BoxCollider>(16 * SCALE, 16 * SCALE);

      auto tank_2 = registry->CreateEntity();
      tank_2.AddComponent<Transform>(glm::vec2(300.0, 0.0));
      tank_2.AddComponent<RigidBody>(glm::vec2(-30.0, 0.0));
      tank_2.AddComponent<Sprite>("tank", 0, 16, 16, 16, glm::vec2(SCALE), true);
      tank_2.AddComponent<Animation>(2, 4);
      tank_2.AddComponent<BoxCollider>(16 * SCALE, 16 * SCALE);
    };

    void ProccessInput() override {
      SDL_Event sdlEvent;
      while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
        case SDL_QUIT:
          state = State::quit;
          break;
        case SDL_KEYDOWN:
          event_bus->Emit<KeyPressedEvent>(sdlEvent.key.keysym.sym, SDL_GetKeyName(sdlEvent.key.keysym.sym));
          if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
            state = State::quit;
          }
          if (sdlEvent.key.keysym.sym == SDLK_d) {
            // toggle debug mode
            if (state == State::debug) {
              state = State::running;
            } else {
              Logger::info("debug mode");
              state = State::debug;
            }
          }
        }
      }
    }
};
