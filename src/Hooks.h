#pragma once
#include "RE/Skyrim.h"

namespace FalconEngine {
    class Hooks {
    public:
        static void Install();
        static void SetShipID(RE::FormID a_id);
        static RE::FormID GetShipID();
    private:
        static void Update();
        static inline REL::Relocation<decltype(Update)> _Update;
    };
}
