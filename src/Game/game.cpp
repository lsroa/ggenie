#include "game.h"
#include "../Logger/logger.h"
#include "../src/Components/rigid_body.h"
#include "../src/Components/transform.h"
#include "../src/System/movement.h"
#include "../src/System/render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <glm/glm.hpp>

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
  width = displayMode.w;
  height = displayMode.h;

  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width - 200, height - 200, SDL_WINDOW_BORDERLESS);
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

void Game::LoadLevel(int level) {
  Logger::log("Loading level " + std::to_string(level));

  /* Register systems */
  registry->AddSystem<Movement>();
  registry->AddSystem<RenderSystem>();

  /* Add textures */
  store->AddTexture(renderer, "tank", "./assets/tank.png");

  /* Create tank */
  auto tank = registry->CreateEntity();
  tank.AddComponent<Transform>();
  tank.AddComponent<RigidBody>(glm::vec2(0.0, 0.0));
  tank.AddComponent<Sprite>("tank", 32, 32);
};

void Game::Setup() {
  Logger::log("Game Setup");
  LoadLevel(1);
}

void Game::Update() {
  int time = MPF - (SDL_GetTicks() - ms);
  if (time > 0) {
    SDL_Delay(time);
  }
  double delta = (SDL_GetTicks() - ms) / 1000.0f;
  ms = SDL_GetTicks();

  /* Call the update of the system */
  registry->GetSystem<Movement>().Update(delta);

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
