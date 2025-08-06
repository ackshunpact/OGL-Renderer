//
// Created by bigbeev on 8/3/2025.
//

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include <cstdint>
#include <unordered_map>
#include "../Components/RenderComponent.h"
using Entity = uint32_t;
class RenderSystem {
public:
    void render(std::unordered_map<Entity, RenderComponent>& renderComponents) {
        for (auto& [entity, component] : renderComponents) {
            printf("component blah");
        }
    }
};



#endif //RENDERSYSTEM_H
