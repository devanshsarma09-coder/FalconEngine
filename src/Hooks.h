// src/Hooks.h
#pragma once

namespace FalconEngine {
    class Hooks {
    public:
        static void Install();
    private:
        static void Update();
        static inline REL::Relocation<decltype(Update)> _Update;
    };
}
