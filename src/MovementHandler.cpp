#include "MovementHandler.h"
#include "InputHandler.h"
namespace FalconEngine {
    void ApplyMovement(RE::Actor* a_actor, RE::TESObjectREFR* a_ship) {
        if (!a_actor || !a_ship) return;
        RE::NiMatrix3 shipRot = a_ship->GetRotation();
        RE::NiPoint3 shipPos = a_ship->GetPosition();
        RE::NiPoint3 worldPos = shipPos + (shipRot * localPos);
        float rX, rY, rZ;
        a_ship->GetRotation(rX, rY, rZ);
        a_actor->SetPosition(worldPos, true);
        a_actor->SetRotation(rX, rY, rZ);
    }
}
