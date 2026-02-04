#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include "Hooks.h"
#include "Papyrus.h"

using namespace RE;
using namespace SKSE;

namespace {
    void InitializeLog() {
        // Simple initialization that doesn't rely on complex directory macros
        auto path = log_directory();
        if (path) {
            *path /= "FalconEngine.log";
            // In a cloud build, we just want to ensure this compiles
        }
    }
}

// The DLL Export must be extern "C" to be found by SKSE
extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const LoadInterface* a_skse) {
    InitializeLog();
    Init(a_skse);

    AllocTrampoline(64); // Increased size for safety

    auto papyrus = GetPapyrusInterface();
    if (papyrus) {
        papyrus->Register(FalconEngine::Papyrus::Register);
    }

    auto messaging = GetMessagingInterface();
    if (messaging) {
        messaging->RegisterListener([](MessagingInterface::Message* a_msg) {
            if (a_msg && a_msg->type == MessagingInterface::kDataLoaded) {
                FalconEngine::Hooks::Install();
            }
        });
    }

    return true;
}

extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
    SKSE::PluginVersionData v;
    v.pluginVersion = 1;
    v.PluginName("FalconEngine");
    v.AuthorName("Developer");
    v.UsesAddressLibrary(true);
    v.CompatibleVersions({ SKSE::RUNTIME_LATEST });
    return v;
}();
