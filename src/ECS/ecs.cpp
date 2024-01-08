#include "ecs.h"
#include <regex>

int IComponent::nextId = 0;

int Entity::GetId() const {
  return id;
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

  if (!free_ids.empty()) {
    id = free_ids.front();
    free_ids.pop_front();
  } else {
    id = len++;
  }

  if (id >= signatures.size()) {
    signatures.resize(id + 1);
  }

  auto entity = std::make_shared<Entity>(id);
  entity->registry = this;
  to_add.insert(*entity);
  Logger::info("Entity created with id: " + std::to_string(id));

  return *entity;
};

void Registry::AddEntityToSystem(Entity entity) {
  const auto entityId = entity.GetId();
  const auto entitySignature = signatures[entityId];

  for (auto &[system_type, system] : systems) {
    const auto systemSignature = system->GetSignature();
    if ((systemSignature & entitySignature) == systemSignature) {
      system->AddEntity(entity);
      Logger::log("Entity " + std::to_string(entityId) + " added to " +
                  system->GetName(system_type));
    }
  }
};

void Registry::RemoveEntityFromSystem(Entity entity) {
  const auto entityId = entity.GetId();
  const auto entitySignature = signatures[entityId];

  for (auto &[system_type, system] : systems) {
    const auto systemSignature = system->GetSignature();
    if ((systemSignature & entitySignature) == systemSignature) {
      system->RemoveEntity(entity);
      Logger::log("Entity " + std::to_string(entityId) + " removed from " +
                  system->GetName(system_type));
    }
  }
}

void Registry::KillEntity(Entity entity) {
  auto id = entity.GetId();
  free_ids.push_back(id);
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
  }
  to_kill.clear();
}
