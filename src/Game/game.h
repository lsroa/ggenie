#pragma once

#include "AssetStore/asset_store.h"
#include "ECS/Systems/animation.h"
#include "ECS/Systems/collision.h"
#include "ECS/Systems/input.h"
#include "ECS/Systems/movement.h"
#include "ECS/Systems/render.h"
#include "ECS/ecs.h"
#include "Utils/logger.h"

#include <GLFW/glfw3.h>
#include <Graphics/sprite_renderer.h>
#include <LDtkLoader/Project.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <memory>

#define SCALE 1

const int FPS = 60;
const int MPF = 1000 / FPS;

enum class State { running, pause, debug, quit };

#define WIDTH 800
#define HEIGHT 600

class Game {
  public:
    Game();
    ~Game() = default;
    State state;
    int width;
    int height;
    GLFWwindow *window;
    std::shared_ptr<SpriteRenderer> renderer;
    std::shared_ptr<Store> store;
    std::shared_ptr<Registry> registry;
    std::unique_ptr<EventBus> event_bus;

    void Setup();
    void Run();
    void Init();

    void Destroy() {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
      glfwTerminate();
    }

    void Update() {
      float delta = (float)glfwGetTime();
      /* int time = MPF - (current - ms); */
      /* if (time > 0) { */
      /*   SDL_Delay(time); */
      /* } */
      /* double delta = (SDL_GetTicks() - ms) / 1000.0f; */
      /* ms = SDL_GetTicks(); */

      /* Clear events */
      event_bus->Reset();
      /* Register events */
      // NOTE: we could do this for common methods like update
      for (const auto &system_pair : registry->GetAllSystems()) {
        system_pair.second->SubscribeToEvents(event_bus);
      }

      /* Call the update of the systems */
      // registry->GetSystem<CollisionSystem>().Update(event_bus);
      /* registry->GetSystem<MovementSystem>().Update(delta); */
      // registry->GetSystem<AnimationSystem>().Update();

      /* Add batched entities */
      registry->Update();
    };

    void Render() {
      glClearColor(0.64, 0.64, 0.65, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      registry->GetSystem<RenderSystem>().Update(renderer, store);

      if (state == State::debug) {
        /* registry->GetSystem<DebugSystem>().Update(renderer); */
      }

      if (state == State::debug) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
      glfwPollEvents();
      glfwSwapBuffers(window);
    };

    void ProccessInput(){

    };

    void LoadLevel(int levelId) {
      Logger::info("Loading level " + std::to_string(levelId));

      /* Register systems */
      // registry->AddSystem<MovementSystem>();
      registry->AddSystem<RenderSystem>();
      // registry->AddSystem<AnimationSystem>();
      // registry->AddSystem<CollisionSystem>();
      /* registry->AddSystem<DebugSystem>(); */
      // registry->AddSystem<InputSystem>();

      // store->AddTexture(renderer, "tilemap", "./assets/tilemap_1.png");
      store->AddTexture(renderer, "tank", "./assets/tank.png");

      /* Load ldtk */
      // ldtk::Project ldtk_project;
      // ldtk_project.loadFromFile("./assets/tank_wars.ldtk");

      // const auto &world = ldtk_project.getWorld();

      // const auto &level = world.getLevel(levelId);

      // const auto &layers = level.allLayers();

      // std::vector<std::string> layer_names;
      // std::transform(layers.rbegin(), layers.rend(), std::back_inserter(layer_names),
      //                [](const ldtk::Layer &l) { return l.getName(); });

      // for (const auto &layer_id : layer_names) {

      //   const auto &layer = level.getLayer(layer_id);

      //   if (!layer.isVisible()) {
      //     continue;
      //   }

      //   const auto &tiles_vector = layer.allTiles();

      //   for (ldtk::Tile tile : tiles_vector) {
      //     auto tile_entity = registry->CreateEntity();
      //     auto [x, y] = tile.getPosition();
      //     auto [tx, ty, w, h] = tile.getTextureRect();
      //     tile_entity.AddComponent<Transform>(glm::vec2(x * SCALE, y * SCALE));
      //     tile_entity.AddComponent<Sprite>("tilemap", tx, ty, w, h, glm::vec2(SCALE));
      //   }
      // }

      auto tank_1 = registry->CreateEntity();
      tank_1.AddComponent<Transform>(glm::vec2(0.0, 0.0));
      tank_1.AddComponent<RigidBody>(glm::vec2(30.0, 0.0));
      tank_1.AddComponent<Sprite>("tank", 0, 16, 16, 16, glm::vec2(SCALE));
      tank_1.AddComponent<Animation>(2, 4);
      tank_1.AddComponent<BoxCollider>(16 * SCALE, 16 * SCALE);

      auto tank_2 = registry->CreateEntity();
      tank_2.AddComponent<Transform>(glm::vec2(100.0, 0.0));
      tank_2.AddComponent<RigidBody>(glm::vec2(-30.0, 0.0));
      tank_2.AddComponent<Sprite>("tank", 0, 16, 16, 16, glm::vec2(SCALE), true);
      tank_2.AddComponent<Animation>(2, 4);
      tank_2.AddComponent<BoxCollider>(16 * SCALE, 16 * SCALE);
    }
};
