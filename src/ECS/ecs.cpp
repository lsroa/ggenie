#include "ecs.h"
#include <algorithm>

int IComponent::nextId = 0;

int Entity::GetId() const {
  return id;
}

/* System */
void System::AddEntity(Entity entity) {

  entities.push_back(entity);
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
  int id = len++;
  if (id >= signatures.size()) {
    signatures.resize(id + 1);
  }

  auto entity = std::make_shared<Entity>(id);
  entity->registry = this;
  toAdd.insert(*entity);
  Logger::log("Entity created with id: " + std::to_string(id));

  return *entity;
};

void Registry::AddEntityToSystem(Entity entity) {
  const auto entityId = entity.GetId();
  const auto entitySignature = signatures[entityId];

  for (auto &[system_type, system] : systems) {
    const auto systemSignature = system->GetSignature();
    if ((systemSignature & entitySignature) == systemSignature) {
      system->AddEntity(entity);
      Logger::log("Entity added to " + std::string(system_type.name()) +
                  " system");
    }
  }
};

void Registry::Update() {
  for (auto entity : toAdd) {
    AddEntityToSystem(entity);
  }
  toAdd.clear();
}
