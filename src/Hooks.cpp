#include "Hooks.h"
#include "MovementHandler.h"
#include "InputHandler.h"
#include "AIPathing.h"
#include "SKSE/SKSE.h"

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
        if (_Update) {
            _Update();
        }

        if (currentShipID == 0) return;

        auto ship = cachedShip.get();
        if (!ship) {
            auto found = RE::TESForm::LookupByID<RE::TESObjectREFR>(currentShipID);
            if (found) cachedShip = found->GetHandle();
            return;
        }

        auto player = RE::PlayerCharacter::GetSingleton();
        if (player && ship.get()) {
            HandleInput();
            ApplyMovement(player, ship.get());
            UpdateCrew(ship.get());
        }
    }

    void Hooks::Install() {
        // Using REL::VariantID for better cross-version support
        REL::Relocation<uintptr_t> target{ REL::ID(35551), 0x11F }; 
        auto& trampoline = SKSE::GetTrampoline();
        _Update = trampoline.write_call<5>(target.address(), reinterpret_cast<uintptr_t>(Update));
    }
}
