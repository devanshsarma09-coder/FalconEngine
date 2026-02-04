#include "Hooks.h"
#include "MovementHandler.h"
#include "InputHandler.h"
#include "AIPathing.h"

namespace FalconEngine {
    static RE::FormID currentShipID = 0;
    static RE::ObjectRefHandle cachedShip;

    void Hooks::SetShipID(RE::FormID a_id) {
        currentShipID = a_id;
        cachedShip = {}; 
    }

    RE::FormID Hooks::GetShipID() {
        return currentShipID;
    }

    void Hooks::Update() {
        _Update();
        if (currentShipID == 0) return;

        auto ship = cachedShip.get();
        if (!ship) {
            auto found = RE::TESForm::LookupByID<RE::TESObjectREFR>(currentShipID);
            if (found) cachedShip = found->GetHandle();
            return;
        }

        auto player = RE::PlayerCharacter::GetSingleton();
        if (player && ship) {
            HandleInput();
            ApplyMovement(player, ship.get());
            UpdateCrew(ship.get());
        }
    }

    void Hooks::Install() {
        // Main Loop Update Hook
        REL::Relocation<uintptr_t> target{ REL::ID(35551), 0x11F }; 
        auto& trampoline = SKSE::GetTrampoline();
        _Update = trampoline.write_call<5>(target.address(), reinterpret_cast<uintptr_t>(Update));
    }
}
