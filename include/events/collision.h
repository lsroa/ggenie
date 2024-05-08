#pragma once
#include "ecs.h"
#include "events/event.h"

class CollisionEvent : public Event {
  public:
    Entity a;
    Entity b;
    CollisionEvent(Entity a, Entity b) : a(a), b(b){};
};
