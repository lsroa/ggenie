#pragma once
#include "ecs.h"
#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>

class Registry {
  private:
    int len = 0;
    std::vector<IPool *> componentPools;
    std::vector<Signature> signatures;
    std::unordered_map<std::type_index, System *> systems;
    std::set<Entity> toAdd;
    std::set<Entity> toKill;
    void Update();

  public:
    Registry() = default;

    Entity CreateEntity();
    /* void KillEntity(Entity entity); */

    void AddComponent(Entity entity);
    IComponent &GetComponent(Entity entity);
    /* void RemoveComponent(Entity entity); */
    void CreateSystem(Signature signature);
};
