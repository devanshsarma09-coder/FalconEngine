// src/Main.cpp
#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "Hooks.h"
#include "Papyrus.h"
using namespace RE;
using namespace SKSE;
SKSEPluginLoad(const LoadInterface* a_skse) {
    Init(a_skse);
    AllocTrampoline(14);
    GetPapyrusInterface()->Register(FalconEngine::Papyrus::Register);
    GetMessagingInterface()->RegisterListener([](MessagingInterface::Message* a_msg) {
        if (a_msg->type == MessagingInterface::kDataLoaded) {
            FalconEngine::Hooks::Install();
        }
    });
    return true;
}
