// src/AIPathing.h
#pragma once
#include "RE/Skyrim.h"
namespace FalconEngine {
    void AddCrewMember(RE::Actor* a_actor, RE::TESObjectREFR* a_ship);
    void UpdateCrew(RE::TESObjectREFR* a_ship);
    void ClearCrewList();
}


