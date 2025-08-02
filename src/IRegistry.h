//
// Created by bigbeev on 8/1/2025.
//

#ifndef IREGISTRY_H
#define IREGISTRY_H
#include <string>

class IRegistry {
public:
    virtual ~IRegistry() = default;

    // optional: helper for downcasting or introspection
    virtual const std::string& typeName() const = 0;
};
#endif //IREGISTRY_H
