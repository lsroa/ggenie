#include "ecs.h"
#include "Components/animation.h"
#include "Components/sprite.h"
#include "Components/transform.h"

#include <regex>

int IComponent::nextId = 0;

/* Component */
template <typename ComponentType>
int Component<ComponentType>::GetId() {
  static int id = nextId++;
  return id;
}

template class Component<Sprite>;
template class Component<Transform>;
template class Component<Animation>;

/* Entity */
int Entity::GetId() const {
  return id;
}

void Entity::KillEntity() {
  registry->KillEntity(*this);
}

/* System */
void System::AddEntity(Entity entity) {

  entities.push_back(entity);
}

std::string System::GetName(std::type_index index) const {
  return std::regex_replace(index.name(), std::regex("[0-9]"), "");
}

void System::RemoveEntity(Entity entity) {
  for (std::vector<Entity>::size_type i = 0; i < entities.size(); i++) {
    auto currentEntity = entities[i];
    if (currentEntity == entity) {
      entities.erase(entities.begin() + i);
    }
  }
}

Signature System::GetSignature() const {
  return signature;
}

std::vector<Entity> System::GetEntities() const {
  return entities;
}

/* Registry */
Entity Registry::CreateEntity() {
  int id;

  if (free_ids.empty()) {
    id = len++;
    if (id >= signatures.size()) {
      signatures.resize(id + 1);
    }
  } else {
    id = free_ids.front();
    free_ids.pop_front();
  }

  auto entity = std::make_shared<Entity>(id);
  entity->registry = this;
  to_add.insert(*entity);
  Logger::info("Entity created with id: " + std::to_string(id));

  return *entity;
};

SystemMap Registry::GetAllSystems() const {
  return this->systems;
}

void Registry::AddEntityToSystem(Entity entity) {
  const auto entityId = entity.GetId();
  Logger::log("Entity id: " + std::to_string(entityId));
  const auto entitySignature = signatures[entityId];
  Logger::log("Entity shape: " + entitySignature.to_string());

  for (auto &[system_type, system] : systems) {
    const auto systemSignature = system->GetSignature();
    if ((systemSignature & entitySignature) == systemSignature) {
      system->AddEntity(entity);
      Logger::log("Entity " + std::to_string(entityId) + " added to " + system->GetName(system_type));
    }
  }
};

void Registry::RemoveEntityFromSystem(Entity entity) {
  /* we could use an std::remove_if */
  const auto entityId = entity.GetId();
  const auto entitySignature = signatures[entityId];

  for (auto &[system_type, system] : systems) {
    const auto systemSignature = system->GetSignature();
    if ((systemSignature & entitySignature) == systemSignature) {
      system->RemoveEntity(entity);
      Logger::log("Entity " + std::to_string(entityId) + " removed from " + system->GetName(system_type));
    }
  }
}

void Registry::KillEntity(Entity entity) {
  auto id = entity.GetId();
  Logger::info("Entity with id: " + std::to_string(id) + " removed");
  to_kill.insert(entity);
};

void Registry::Update() {
  // Add entities
  for (auto entity : to_add) {
    AddEntityToSystem(entity);
  }
  to_add.clear();

  // Remove entities
  for (auto entity : to_kill) {
    RemoveEntityFromSystem(entity);
    signatures[entity.GetId()].reset();
    free_ids.push_back(entity.GetId());
  }
  to_kill.clear();
}
