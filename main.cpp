#include "src/Renderer.h"
#include "src/ECS/Core/ECS.h"

using Entity=uint32_t;

int main() {

    Renderer* renderer = new Renderer();

    renderer->Run();
    // struct RenderComponent {
    //     void render() {
    //         std::cout << "Rendering\n";
    //     }
    // };
    //
    // struct UpdateComponent {
    //     void update(float dt) {
    //         std::cout << "Updating: " << dt << "\n";
    //     }
    // };
    //
    // ECS ecs;
    // Entity block = ecs.createEntity();
    //
    // ecs.addComponent(block, RenderComponent());
    // ecs.addComponent(block, UpdateComponent());
    //
    // // Render system
    // for (auto& [entity, rc] : ecs.getAllComponents<RenderComponent>()) {
    //     rc.render();
    // }
    //
    // // Update system
    // for (auto& [entity, uc] : ecs.getAllComponents<UpdateComponent>()) {
    //     uc.update(0.016f);
    // }
    //

    return 0;
}


