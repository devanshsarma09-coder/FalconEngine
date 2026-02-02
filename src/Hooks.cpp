// src/Hooks.cpp
#include "Hooks.h"
#include "MovementHandler.h"
#include "InputHandler.h"
#include "AIPathing.h"

namespace FalconEngine {
    void Hooks::Update() {
        _Update(); // Execute original game code first

        auto player = RE::PlayerCharacter::GetSingleton();
        auto dragon = RE::TESForm::LookupByID<RE::TESObjectREFR>(0x00012345);

        if (player && dragon) {
            HandleInput();
            ApplyMovement(player, dragon);
            UpdateCrew(dragon);
        }
    }

    void Hooks::Install() {
        // REL::ID(35551) is the Main Loop for SE/AE
        REL::Relocation<uintptr_t> target{ REL::ID(35551), 0x11F }; 
        
        auto& trampoline = SKSE::GetTrampoline();
        _Update = trampoline.write_call<5>(target.address(), reinterpret_cast<uintptr_t>(Update));
    }
}
