#pragma once

#include "ECS/Events/event_bus.h"
#include "ECS/ecs.h"

#include <memory>

#define SCALE 3

const int FPS = 60;
const int MPF = 1000 / FPS;

enum class State { running, pause, debug, quit };

class Game {
  public:
    State state;
    int width;
    int height;
    std::shared_ptr<Registry> registry;
    std::unique_ptr<EventBus> event_bus;

    void Setup();
    void Run();

    virtual void Init() = 0;
    virtual void Destroy() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void ProccessInput() = 0;
    virtual void LoadLevel(int levelId) = 0;
};
