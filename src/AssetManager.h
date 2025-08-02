//
// Created by bigbeev on 8/1/2025.
//

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <memory>

#include "ImageRegistry.h"

enum class Registries {
    Image = 0,
    Texture,
    Mesh
};

class AssetManager {
public:
    static std::unordered_map<std::string, std::shared_ptr<IRegistry>> registries;

    template <typename T>
    static std::shared_ptr<Registry<T>> getRegistry(const std::string& key) {
        auto it = registries.find(key);
        if (it == registries.end()) return nullptr;

        return std::dynamic_pointer_cast<Registry<T>>(it->second);
    }

    template <typename T>
    static std::shared_ptr<T> getAsset(const std::string& registryKey, const std::string& assetName) {
        auto registry = getRegistry<T>(registryKey);
        if (registry) {
            return registry->get(assetName);
        }
        return nullptr;
    }
};

// static member definition
std::unordered_map<std::string, std::shared_ptr<IRegistry>> AssetManager::registries;

#endif //ASSETMANAGER_H
