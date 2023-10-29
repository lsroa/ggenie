#pragma once
#include "../src/Logger/logger.h"
#include "ecs.h"
#include <cstddef>
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

/*
 * 			Signature    [ 1 | 0 | 1 | 0 ]
 *
 *
 *     ComponentType [ T1, T2, T3, T4]
 *     componentPools[*P1,*P2,*P3,*P4]
 *								[E1][C1,
 *								[E2] C2,
 *								[E3] C3,
 *								[E4] C4]
 */

class Registry {
  private:
    int len = 0;
    std::vector<std::shared_ptr<IPool>> componentPools;
    std::vector<Signature> signatures;
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
    std::set<Entity> toAdd;
    std::set<Entity> toKill;

  public:
    Registry() = default;

    Entity CreateEntity();

    /* Components */
    template <typename ComponentType, typename... ComponentArgs>
    void AddComponent(Entity entity, ComponentArgs &&...args);
    template <typename T>
    T &GetComponent(Entity entity);
    template <typename T>
    bool HasComponent(Entity entity);
    template <typename T>
    void RemoveComponent(Entity entity);

    /* Systems */
    template <typename T, typename... Args>
    void AddSystem(Args &&...args);
    template <typename T>
    void RemoveSystem();
    template <typename T>
    bool HasSystem() const;
    template <typename T>
    T &GetSystem() const;

    void AddEntityToSystem(Entity entity);
    void Update();
};

/* System */
template <typename T, typename... Args>
void Registry::AddSystem(Args &&...args) {
  const auto value = std::make_shared<T>(std::forward<Args>(args)...);
  const auto key = std::type_index(typeid(T));
  systems.insert(std::make_pair(key, value));
};

template <typename TSystem>
TSystem &Registry::GetSystem() const {
  auto system = systems.find(std::type_index(typeid(TSystem)));
  return std::static_pointer_cast<std::shared_ptr<TSystem>>(system->second);
};

template <typename TSystem>
void Registry::RemoveSystem() {
  auto system = systems.find(std::type_index(typeid(TSystem)));
  systems.erase(system);
};

template <typename T>
bool Registry::HasSystem() const {
  return systems.find(std::type_index(typeid(T))) != systems.end();
};

/* Component */

template <typename ComponentType, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs &&...args) {
  const int componentId = Component<ComponentType>::GetId();
  const int entityId = entity.GetId();

  if (componentId >= componentPools.size()) {
    componentPools.resize(componentId + 1, nullptr);
  }

  if (!componentPools[componentId]) {
    componentPools[componentId] = std::make_shared<Pool<ComponentType>>();
  }

  /* why do we need to cast this ? */
  std::shared_ptr<Pool<ComponentType>> pool =
      std::static_pointer_cast<Pool<ComponentType>>(
          componentPools[componentId]);

  if (pool->GetSize() <= entityId) {
    pool->Resize(len);
  }

  ComponentType component = ComponentType(std::forward<TArgs>(args)...);

  pool->Set(entityId, component);
  Logger::log(
      static_cast<std::string>(std::type_index(typeid(ComponentType)).name()) +
      " component added to entity: " + std::to_string(entityId));
  signatures[entityId].set(componentId);
};

template <typename T>
T &Registry::GetComponent(Entity entity) {
  auto componentId = Component<T>::GetId();
  auto entityId = entity.GetId();
  T &component = Component<T>(componentPools[componentId][entityId]);

  return component;
};

template <typename T>
bool Registry::HasComponent(Entity entity) {
  auto componentId = Component<T>::GetId();
  auto entityId = entity.GetId();

  return signatures[entityId].test(componentId);
}

template <typename T>
void Registry::RemoveComponent(Entity entity) {
  auto entityId = entity.GetId();
  auto componentId = Component<T>::GetId();

  signatures[entityId].set(componentId, false);
};
