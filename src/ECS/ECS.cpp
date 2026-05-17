#include "ECS.h"
#include <algorithm>
uint64_t Entity::GetID() const {
    return id;
}

void System::AddEntityToSystem(Entity entity) {
    entities.emplace_back(std::move(entity));
}

void System::RemoveEntityFromSystem(Entity entity) {

    for (size_t i = 0; i < entities.size(); ++i) {
        if (entities[i] == entity) {
            entities[i] = std::move(entities.back());
            entities.pop_back();
            break;
        }
    }

    return;
}

std::vector<Entity> System::GetSystemEntities() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}
