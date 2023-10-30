#include "game.h"
#include "../Logger/logger.h"
#include "../src/Components/rigid_body.h"
#include "../src/Components/transform.h"
#include "glm/glm.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <glm/glm.hpp>
#include <iostream>

Game::Game() {
  Logger::log("Game spawn");
  registry = std::make_shared<Registry>();
}
Game::~Game() {
  Logger::log("Game despawn");
}

void Game::Init() {
  Logger::log("Game init");
  int result = SDL_Init(SDL_INIT_EVERYTHING);
  if (result != 0) {
    Logger::err("Error SDL init");
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

void Game::Setup() {
  Logger::log("Game Setup");
  auto tank = registry->CreateEntity();
  tank.AddComponent<Transform>();
  tank.AddComponent<RigidBody>();

  auto tank_position = tank.GetComponent<Transform>().position;
  Logger::log("tank position: " + std::to_string(tank_position.y) + " " +
              std::to_string(tank_position.x));
}

void Game::Update() {
  int time = MPF - (SDL_GetTicks() - ms);
  if (time > 0) {
    SDL_Delay(time);
  }
  /* double delta = (SDL_GetTicks() - ms) / 1000.0f; */
  /* ms = SDL_GetTicks(); */
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
