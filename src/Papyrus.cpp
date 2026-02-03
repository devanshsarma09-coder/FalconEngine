#include "Papyrus.h"
#include "MovementHandler.h"
#include "AIPathing.h"
#include "Hooks.h" // To access the ship variable

namespace FalconEngine {
    
    // Command: FalconEngine.SetShip(ObjectReference akShip)
    void SetShip(RE::StaticFunctionTag*, RE::TESObjectREFR* a_ship) {
        if (!a_ship) return;
        FalconEngine::Hooks::SetShipID(a_ship->GetFormID());
    }

    // Command: FalconEngine.AddCrew(Actor akActor)
    void AddCrew(RE::StaticFunctionTag*, RE::Actor* a_actor) {
        if (!a_actor) return;
        
        // Save where they are relative to the ship right now
        // This locks them to their current spot on the deck
        RE::ObjectRefHandle handle = a_actor->GetHandle();
        
        // We need to calculate the initial offset
        auto ship = RE::TESForm::LookupByID<RE::TESObjectREFR>(FalconEngine::Hooks::GetShipID());
        if (ship) {
            RE::NiPoint3 offset = a_actor->GetPosition() - ship->GetPosition();
            RE::NiMatrix3 invRot = ship->GetRotation().Transpose();
            
            FalconEngine::crewLocalCoords[handle] = invRot * offset;
        }
    }

    // Command: FalconEngine.ClearCrew()
    void ClearCrew(RE::StaticFunctionTag*) {
        FalconEngine::crewLocalCoords.clear();
    }

    bool Register(RE::BSScript::IVirtualMachine* a_vm) {
        a_vm->RegisterFunction("SetShip", "FalconEngine", SetShip);
        a_vm->RegisterFunction("AddCrew", "FalconEngine", AddCrew);
        a_vm->RegisterFunction("ClearCrew", "FalconEngine", ClearCrew);
        return true;
    }
}
