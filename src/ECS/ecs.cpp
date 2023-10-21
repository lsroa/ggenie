#include "ecs.h"
#include <algorithm>

int Entity::GetId() const {
  return id;
}

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
