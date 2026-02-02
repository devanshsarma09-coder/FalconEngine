#pragma once
#include "RE/Skyrim.h"
#include <map>
namespace FalconEngine {
    extern std::map<RE::FormID, RE::NiPoint3> crewLocalCoords;
    void UpdateCrew(RE::TESObjectREFR* a_ship);
}
