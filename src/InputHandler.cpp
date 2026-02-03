// src/InputHandler.cpp
#include "InputHandler.h"
namespace FalconEngine {
    RE::NiPoint3 localPos = { 0.0f, 0.0f, 10.0f };
    float speed = 350.0f;
    void HandleInput() {
        auto input = RE::ControlMap::GetSingleton();
        float delta = 0.016f;
        if (input && input->IsActivatePrimaryDown()) {
            localPos.y += speed * delta;
        }
        if (input && input->IsActivateSecondaryDown()) {
            localPos.y -= speed * delta;
        }
        if (input && input->IsMoveButtonDown()) { // A/D keys usually mapped to MoveLeft/Right
           // Logic for Strafe can be added here
        }
    }
}


