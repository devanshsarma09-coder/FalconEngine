#include "Papyrus.h"
#include "Hooks.h"
#include "AIPathing.h"

namespace FalconEngine::Papyrus {
    void SetShip(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ship) {
        if (!a_ship) return;
        FalconEngine::Hooks::SetShipID(a_ship->GetFormID());
    }

    void AddCrew(RE::StaticFunctionTag*, RE::Actor* a_actor) {
        if (!a_actor) return;
        auto shipID = FalconEngine::Hooks::GetShipID();
        if (shipID == 0) return;
        
        auto ship = RE::TESForm::LookupByID<RE::TESObjectREFR>(shipID);
        if (ship) {
            FalconEngine::AddCrewMember(a_actor, ship);
        }
    }

    void ClearCrew(RE::StaticFunctionTag*) {
        FalconEngine::ClearCrewList();
    }

    bool Register(RE::BSScript::IVirtualMachine* a_vm) {
        a_vm->RegisterFunction("SetShip", "FalconEngine", SetShip);
        a_vm->RegisterFunction("AddCrew", "FalconEngine", AddCrew);
        a_vm->RegisterFunction("ClearCrew", "FalconEngine", ClearCrew);
        return true;
    }
}
