// src/Main.cpp
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "Hooks.h"

using namespace RE;
using namespace SKSE;

SKSEPluginLoad(const LoadInterface* a_skse) {
    Init(a_skse);

    // Allocate 14 bytes for a standard 5-byte branch hook
    AllocTrampoline(14); 

    GetMessagingInterface()->RegisterListener([](MessagingInterface::Message* a_msg) {
        if (a_msg->type == MessagingInterface::kDataLoaded) {
            FalconEngine::Hooks::Install();
        }
    });

    return true;
}
