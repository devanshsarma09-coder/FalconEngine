#include "MovementHandler.h"
#include "InputHandler.h"

namespace FalconEngine {
    void ApplyMovement(RE::Actor* a_actor, RE::TESObjectREFR* a_ship) {
        if (!a_actor || !a_ship) return;
        
        auto root = a_ship->Get3D();
        if (!root) return;

        RE::NiMatrix3 shipRot = root->world.rotate;
        RE::NiPoint3 shipPos = root->world.translate;
        
        // global localPos from InputHandler
        RE::NiPoint3 worldPos = shipPos + (shipRot * localPos);
        
        a_actor->SetPosition(worldPos, true);
        
        float rX, rY, rZ;
        shipRot.ToEulerAnglesXYZ(rX, rY, rZ);
        a_actor->SetRotation(rX, rY, rZ);
    }
}
