#pragma once
#include "ECS/Events/event.h"
#include "ECS/ecs.h"

class CollisionEvent : public Event {
  public:
    Entity a;
    Entity b;
    CollisionEvent(Entity a, Entity b) : a(a), b(b){};
};
