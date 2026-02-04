#pragma once
#include "RE/Skyrim.h"

namespace FalconEngine {
    // These must be defined as extern to be seen by MovementHandler
    extern RE::NiPoint3 localPos;
    extern float speed;
    
    void HandleInput();
}
