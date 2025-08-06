//
// Created by bigbeev on 8/3/2025.
//

#ifndef ECS_H
#define ECS_H



#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <typeindex>
#include <type_traits>
#include <cstdint>
#include <cassert>

using Entity = std::uint32_t;

class ECS {
public:
    ECS() : nextEntityId(1) {}

    // === Entity Management ===

    Entity createEntity() {
        Entity id = nextEntityId++;
        activeEntities.insert(id);
        return id;
    }

    void destroyEntity(Entity entity) {
        activeEntities.erase(entity);
        // Remove all components tied to this entity
        for (auto& [type, map] : componentStores) {
            map->remove(entity);
        }
    }

    const std::unordered_set<Entity>& getEntities() const {
        return activeEntities;
    }

    // === Component Management ===

    template<typename ComponentType>
    void addComponent(Entity entity, ComponentType component) {
        getOrCreateComponentStore<ComponentType>()->components[entity] = component;
    }

    template<typename ComponentType>
    void removeComponent(Entity entity) {
        auto store = getComponentStore<ComponentType>();
        if (store) store->components.erase(entity);
    }

    template<typename ComponentType>
    bool hasComponent(Entity entity) const {
        auto store = getComponentStore<ComponentType>();
        return store && store->components.count(entity) > 0;
    }

    template<typename ComponentType>
    ComponentType* getComponent(Entity entity) {
        auto store = getComponentStore<ComponentType>();
        if (store && store->components.count(entity)) {
            return &store->components[entity];
        }
        return nullptr;
    }

    // === Component Iteration (for systems) ===

    template<typename ComponentType>
    std::unordered_map<Entity, ComponentType>& getAllComponents() {
        return getOrCreateComponentStore<ComponentType>()->components;
    }

private:
    Entity nextEntityId;
    std::unordered_set<Entity> activeEntities;

    struct IComponentStore {
        virtual ~IComponentStore() = default;
        virtual void remove(Entity entity) = 0;
    };

    template<typename T>
    struct ComponentStore : IComponentStore {
        std::unordered_map<Entity, T> components;

        void remove(Entity entity) override {
            components.erase(entity);
        }
    };

    std::unordered_map<std::type_index, std::shared_ptr<IComponentStore>> componentStores;

    template<typename T>
    std::shared_ptr<ComponentStore<T>> getComponentStore() const {
        auto it = componentStores.find(std::type_index(typeid(T)));
        if (it != componentStores.end()) {
            return std::static_pointer_cast<ComponentStore<T>>(it->second);
        }
        return nullptr;
    }

    template<typename T>
    std::shared_ptr<ComponentStore<T>> getOrCreateComponentStore() {
        auto typeId = std::type_index(typeid(T));
        if (componentStores.count(typeId) == 0) {
            componentStores[typeId] = std::make_shared<ComponentStore<T>>();
        }
        return std::static_pointer_cast<ComponentStore<T>>(componentStores[typeId]);
    }
};

#endif //ECS_H
