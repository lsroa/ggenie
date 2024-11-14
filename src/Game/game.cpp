#include "game.h"

void Game::Run() {
  Setup();
  while (state == State::running || state == State::debug) {
    ProccessInput();
    Update();
    Render();
  }
}

void Game::Setup() {
  Logger::info("Game Setup");
  LoadLevel(0);
}
