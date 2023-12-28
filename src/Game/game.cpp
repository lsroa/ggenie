#include "game.h"
#include "../Logger/logger.h"
#include "../libs/ldtk/include/LDtkLoader/Project.hpp"
#include "../src/Components/rigid_body.h"
#include "../src/Components/transform.h"
#include "../src/System/movement.h"
#include "../src/System/render.h"
#include "glm/ext/vector_float2.hpp"
#include <LDtkLoader/Layer.hpp>
#include <LDtkLoader/Tile.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <glm/glm.hpp>
#include <string>
#define SCALE 4

Game::Game() {
  Logger::log("Game spawn");
  registry = std::make_shared<Registry>();
  store = std::make_unique<Store>();
}
Game::~Game() {
  Logger::log("Game despawn");
}

void Game::Init() {
  Logger::log("Game init");

  int result = SDL_Init(SDL_INIT_VIDEO);
  if (result != 0) {
    Logger::err("Error SDL init video");
    return;
  }

  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);
  /* width = displayMode.w; */
  /* height = displayMode.h; */
  this->width = 320 * SCALE;
  this->height = 192 * SCALE;

  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       this->width, this->height, SDL_WINDOW_BORDERLESS);
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

void Game::Run() {
  Setup();
  while (state == State::running) {
    ProccessInput();
    Update();
    Render();
  }
}

void Game::ProccessInput() {
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
    case SDL_QUIT:
      state = State::quit;
      break;
    case SDL_KEYDOWN:
      if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
        state = State::quit;
      }
    }
  }
}

void Game::LoadLevel(int levelId) {
  Logger::log("Loading level " + std::to_string(levelId));

  /* Register systems */
  registry->AddSystem<MovementSystem>();
  registry->AddSystem<RenderSystem>();

  /* Load ldtk */
  ldtk::Project ldtk_project;
  ldtk_project.loadFromFile("./assets/tank_wars.ldtk");
  store->AddTexture(renderer, "tilemap", "./assets/tilemap_1.png");

  const auto &world = ldtk_project.getWorld();

  const auto &level = world.getLevel(levelId);

  std::string layers[] = {"Floor_1", "Water"};

  for (const auto &layer_id : layers) {

    const auto &layer = level.getLayer(layer_id);

    const auto &tiles_vector = layer.allTiles();

    for (ldtk::Tile tile : tiles_vector) {
      auto tile_entity = registry->CreateEntity();
      auto [x, y] = tile.getPosition();
      auto [tx, ty, w, h] = tile.getTextureRect();
      tile_entity.AddComponent<Transform>(glm::vec2(x * SCALE, y * SCALE));
      tile_entity.AddComponent<Sprite>("tilemap", tx, ty, w, h,
                                       glm::vec2(SCALE));
    }
  }

  /* Add textures */
  store->AddTexture(renderer, "tank", "./assets/tank_1.png");

  /* Create tank */
  auto tank = registry->CreateEntity();
  tank.AddComponent<Transform>();
  tank.AddComponent<RigidBody>(glm::vec2(1.0, 0.0));
  tank.AddComponent<Sprite>("tank", 32, 32);
};

void Game::Setup() {
  Logger::log("Game Setup");
  LoadLevel(0);
}

void Game::Update() {
  int time = MPF - (SDL_GetTicks() - ms);
  if (time > 0) {
    SDL_Delay(time);
  }
  double delta = (SDL_GetTicks() - ms) / 1000.0f;
  ms = SDL_GetTicks();

  /* Call the update of the system */
  registry->GetSystem<MovementSystem>().Update(delta);

  /* Add batched entities */
  registry->Update();
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
  SDL_RenderClear(renderer);

  registry->GetSystem<RenderSystem>().Update(renderer, store);

  /* swap back with front buffer */
  SDL_RenderPresent(renderer);
}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
