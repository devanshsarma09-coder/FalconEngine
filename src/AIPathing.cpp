#include "AIPathing.h"
namespace FalconEngine {
    std::map<RE::FormID, RE::NiPoint3> crewLocalCoords;
    void UpdateCrew(RE::TESObjectREFR* a_ship) {
        if (!a_ship) return;
        RE::NiMatrix3 shipRot = a_ship->GetRotation();
        RE::NiPoint3 shipPos = a_ship->GetPosition();
        for (auto& [id, local] : crewLocalCoords) {
            auto crew = RE::TESForm::LookupByID<RE::Actor>(id);
            if (crew) {
                RE::NiPoint3 worldPos = shipPos + (shipRot * local);
                crew->SetPosition(worldPos, true);
            }
        }
    }
}
