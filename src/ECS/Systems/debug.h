#pragma once
#include "ECS/Components/collider.h"
#include "ECS/Components/transform.h"

#include "ECS/ecs.h"

class DebugSystem : public System {
  public:
    DebugSystem() {
      RequireComponent<BoxCollider>();
      RequireComponent<Transform>();
    }
};
