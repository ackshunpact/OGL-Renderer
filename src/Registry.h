//
// Created by bigbeev on 8/1/2025.
//

#ifndef REGISTRY_H
#define REGISTRY_H
#include <memory>
#include <string>
#include <unordered_map>
#include "IRegistry.h"


template <typename T>
class Registry : public IRegistry {
public:
    virtual ~Registry() = default;

    std::unordered_map<std::string, std::shared_ptr<T>> assets;
    virtual std::shared_ptr<T> get(const std::string &name) = 0;
    virtual void insert(const std::string &name, const std::string& path) = 0;
    const std::string& typeName() const override {
        static const std::string name = typeid(T).name();
        return name;
    }

};



#endif //REGISTRY_H
