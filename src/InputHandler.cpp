#include "InputHandler.h"

namespace FalconEngine {
    // Actual memory allocation for the variables
    RE::NiPoint3 localPos = { 0.0f, 0.0f, 100.0f };
    float speed = 350.0f;

    void HandleInput() {
        auto input = RE::ControlMap::GetSingleton();
        if (!input) return;

        float delta = 0.016f; // Approximate frame time
        
        if (input->IsActivatePrimaryDown()) {
            localPos.y += speed * delta;
        }
        if (input->IsActivateSecondaryDown()) {
            localPos.y -= speed * delta;
        }
    }
}
