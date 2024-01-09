#pragma once
#include "logger.h"
#include <bitset>
#include <memory>
#include <regex>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

const unsigned int MAX_COMPONENTS = 8;
typedef std::bitset<MAX_COMPONENTS> Signature;

class IComponent {
  protected:
    static int nextId;
};

template <typename ComponentType>
class Component : public IComponent {
  public:
    static int GetId() {
      /* this static makes the id to be "cached" for the next call of the
       * function */
      static auto id = nextId++;
      return id;
    }
};

class IPool {
  public:
    virtual ~IPool(){};
};

template <typename T>
class Pool : public IPool {
  private:
    std::vector<T> data;

  public:
    Pool(int size = 20) {
      Resize(size);
    }

    ~Pool() = default;

    void Resize(int n) {
      data.resize(n);
    }

    void Add(T obj) {
      data.push_back(obj);
    }

    T &Get(int id) {
      return data[id];
    }

    void Set(int id, T obj) {
      data[id] = obj;
    }

    int GetSize() {
      return data.size();
    }
};

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

class System {
  private:
    Signature signature;
    std::vector<class Entity> entities;

  public:
    System() = default;
    ~System() = default;
    void AddEntity(Entity entity);
    void RemoveEntity(Entity entity);
    std::string GetName(std::type_index) const;
    std::vector<Entity> GetEntities() const;
    Signature GetSignature() const;
    template <typename ComponentType>
    void RequireComponent();
};

template <typename ComponentType>
void System::RequireComponent() {
  const auto componentId = Component<ComponentType>::GetId();
  signature.set(componentId);
}

class Entity {
  private:
    int id;

  public:
    Entity(int id) : id(id){};
    int GetId() const;
    class Registry *registry;
    void KillEntity();

    /* Operators */
    Entity &operator=(const Entity &other) = default;
    bool operator==(const Entity &other) const {
      return id == other.id;
    }
    bool operator!=(const Entity &other) const {
      return id != other.id;
    }
    bool operator>(const Entity &other) const {
      return id > other.id;
    }
    bool operator<(const Entity &other) const {
      return id < other.id;
    }

    /* Components */
    template <typename ComponentType, typename... ComponentArgs>
    void AddComponent(ComponentArgs &&...args);
    template <typename T>
    T &GetComponent() const;
    template <typename T>
    bool HasComponent() const;
    template <typename T>
    void RemoveComponent();
};

/**
 *  Class of registry
 */
class Registry {
  private:
    // number of Entities
    int len = 0;
    // All the systems
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
    // Queue for adding enitties
    std::set<Entity> to_add;
    // Queue for killing entities
    std::set<Entity> to_kill;
    // It holds the signature of every entity using the id of the entity as
    // index
    std::vector<Signature> signatures;
    // It holds the components of every entity using the id of the entity as
    // index
    std::vector<std::shared_ptr<IPool>> component_pools;
    // Queue of reusable ids
    std::deque<int> free_ids;

  public:
    Registry() = default;

    /* Entity */
    Entity CreateEntity();
    void AddEntityToSystem(Entity entity);
    void RemoveEntityFromSystem(Entity entity);
    void KillEntity(Entity entity);

    /* Components */
    template <typename ComponentType, typename... ComponentArgs>
    void AddComponent(Entity entity, ComponentArgs &&...args);
    template <typename T>
    T &GetComponent(Entity entity) const;
    template <typename T>
    bool HasComponent(Entity entity) const;
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

    void Update();
};

/* Manage System */
template <typename T, typename... Args>
void Registry::AddSystem(Args &&...args) {
  const auto value = std::make_shared<T>(std::forward<Args>(args)...);
  const auto key = std::type_index(typeid(T));
  systems.insert(std::make_pair(key, value));
};

template <typename TSystem>
TSystem &Registry::GetSystem() const {
  auto system = systems.find(std::type_index(typeid(TSystem)));
  return *(std::static_pointer_cast<TSystem>(system->second));
}

template <typename TSystem>
void Registry::RemoveSystem() {
  auto system = systems.find(std::type_index(typeid(TSystem)));
  systems.erase(system);
};

template <typename T>
bool Registry::HasSystem() const {
  return systems.find(std::type_index(typeid(T))) != systems.end();
};

/* Manage Component */

template <typename ComponentType, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs &&...args) {
  const int componentId = Component<ComponentType>::GetId();
  const int entityId = entity.GetId();

  if (componentId >= component_pools.size()) {
    component_pools.resize(componentId + 1, nullptr);
  }

  if (!component_pools[componentId]) {
    component_pools[componentId] = std::make_shared<Pool<ComponentType>>();
  }

  /* why do we need to cast this ? */
  std::shared_ptr<Pool<ComponentType>> pool =
      std::static_pointer_cast<Pool<ComponentType>>(
          component_pools[componentId]);

  if (pool->GetSize() <= entityId) {
    pool->Resize(len);
  }

  ComponentType component = ComponentType(std::forward<TArgs>(args)...);

  pool->Set(entityId, component);
  const auto component_name = std::regex_replace(
      static_cast<std::string>(std::type_index(typeid(ComponentType)).name()),
      std::regex("[0-9]"), "");
  Logger::log(component_name +
              " component added to entity: " + std::to_string(entityId));
  signatures[entityId].set(componentId);
};

template <typename T>
T &Registry::GetComponent(Entity entity) const {
  const auto componentId = Component<T>::GetId();
  const auto entityId = entity.GetId();
  auto pool = std::static_pointer_cast<Pool<T>>(component_pools[componentId]);
  return pool->Get(entityId);
};

template <typename T>
bool Registry::HasComponent(Entity entity) const {
  auto componentId = Component<T>::GetId();
  auto entityId = entity.GetId();

  return signatures[entityId].test(componentId);
}

template <typename T>
void Registry::RemoveComponent(Entity entity) {
  auto entityId = entity.GetId();
  auto componentId = Component<T>::GetId();

  signatures[entityId].set(componentId, false);
}

/* Entity */

template <typename ComponentType, typename... TArgs>
void Entity::AddComponent(TArgs &&...args) {
  registry->AddComponent<ComponentType>(*this, std::forward<TArgs>(args)...);
}

template <typename T>
T &Entity::GetComponent() const {
  return registry->GetComponent<T>(*this);
}

template <typename T>
bool Entity::HasComponent() const {
  return registry->HasComponent<T>(*this);
}

template <typename T>
void Entity::RemoveComponent() {
  return registry->RemoveComponent<T>(*this);
}
