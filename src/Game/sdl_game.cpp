#include "sdl_game.h"

SDLGame::SDLGame() {
  Logger::info("Game spawn");
  registry = std::make_shared<Registry>();
  store = std::make_unique<SDLStore>();
  event_bus = std::make_unique<EventBus>();
}

SDLGame::~SDLGame() {
  Logger::info("Game despawn");
}
