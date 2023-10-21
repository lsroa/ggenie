#pragma once
#include <bitset>
#include <vector>
const unsigned int MAX_COMPONENTS = 8;
typedef std::bitset<MAX_COMPONENTS> Signature;

class IComponent {
  protected:
    static int nextId;
};

template <typename ComponentType>
class Component : public IComponent {
    int id;
    static int GetId() {
      static auto id = nextId++;
      return id;
    }
};

class Entity {
  private:
    int id;

  public:
    Entity(int id) : id(id){};
    int GetId() const;

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
};

class System {
  private:
    Signature signature;
    std::vector<Entity> entities;

  public:
    System() = default;
    ~System() = default;
    void AddEntity(Entity entity);
    void RemoveEntity(Entity entity);
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

class IPool {
  public:
    virtual void Add() = 0;
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
};
