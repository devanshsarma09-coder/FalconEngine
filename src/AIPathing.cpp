// src/AIPathing.cpp
#include "AIPathing.h"
#include <map>
namespace FalconEngine {
    std::map<RE::ObjectRefHandle, RE::NiPoint3> crewLocalCoords;
    void AddCrewMember(RE::Actor* a_actor, RE::TESObjectREFR* a_ship) {
        if (!a_actor || !a_ship) return;
        RE::NiPoint3 offset = a_actor->GetPosition() - a_ship->GetPosition();
        RE::NiMatrix3 invRot = a_ship->GetRotation().Transpose();
        crewLocalCoords[a_actor->GetHandle()] = invRot * offset;
    }
    void UpdateCrew(RE::TESObjectREFR* a_ship) {
        if (!a_ship) return;
        RE::NiMatrix3 shipRot = a_ship->GetRotation();
        RE::NiPoint3 shipPos = a_ship->GetPosition();
        for (auto it = crewLocalCoords.begin(); it != crewLocalCoords.end();) {
            auto crew = it->first.get();
            if (crew && !crew->IsDisabled() && crew->GetParentCell()) {
                RE::NiPoint3 worldPos = shipPos + (shipRot * it->second);
                crew->SetPosition(worldPos, true);
                ++it;
            } else {
                it = crewLocalCoords.erase(it);
            }
        }
    }
    void ClearCrewList() {
        crewLocalCoords.clear();
    }
}

    


