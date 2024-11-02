#pragma once

#define SCALE 3

#include "AssetStore/asset_store.h"
#include "ECS/Events/event_bus.h"
#include "ECS/ecs.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <memory>

const int FPS = 60;
const int MPF = 1000 / FPS;

enum class State { running, pause, debug, quit };

class Game {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int ms = 0;
    std::shared_ptr<Registry> registry;
    std::shared_ptr<Store> store;
    std::unique_ptr<EventBus> event_bus;

  public:
    State state;
    Game();
    ~Game();
    void Destroy();
    void Init();
    void ProccessInput();
    void Render();
    void Setup();
    void LoadLevel(int level);
    void Run();
    void Update();
    int width;
    int height;
};
