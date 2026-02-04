#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "Hooks.h"
#include "Papyrus.h"

using namespace RE;
using namespace SKSE;

namespace {
    void InitializeLog() {
        auto path = log_directory();
        if (!path) return;
        *path /= "FalconEngine.log";
        // Simple console-like logging for the cloud build
    }
}

SKSEPluginLoad(const LoadInterface* a_skse) {
    InitializeLog();
    Init(a_skse);

    AllocTrampoline(14);

    auto papyrus = GetPapyrusInterface();
    if (papyrus) {
        papyrus->Register(FalconEngine::Papyrus::Register);
    }

    auto messaging = GetMessagingInterface();
    if (messaging) {
        messaging->RegisterListener([](MessagingInterface::Message* a_msg) {
            if (a_msg->type == MessagingInterface::kDataLoaded) {
                FalconEngine::Hooks::Install();
            }
        });
    }

    return true;
}

