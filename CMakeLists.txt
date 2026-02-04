cmake_minimum_required(VERSION 3.24)
project(FalconEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force Skyrim AE
set(SKYRIM_AE ON CACHE BOOL "" FORCE)

# Manually include the libraries we downloaded in the build script
# 1. FMT
add_subdirectory(${FMT_PATH} build/fmt EXCLUDE_FROM_ALL)

# 2. SPDLOG
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)
add_subdirectory(${SPDLOG_PATH} build/spdlog EXCLUDE_FROM_ALL)

# 3. CommonLibSSE-NG
# We tell it not to find_package anything because we are providing the targets
add_subdirectory(${COMMONLIB_PATH} build/commonlib EXCLUDE_FROM_ALL)

add_library(${PROJECT_NAME} SHARED
    "src/Main.cpp"
    "src/Hooks.cpp"
    "src/Papyrus.cpp"
    "src/MovementHandler.cpp"
    "src/InputHandler.cpp"
    "src/AIPathing.cpp"
)

# Link the targets directly
target_link_libraries(${PROJECT_NAME} PRIVATE 
    commonlibsse-ng::commonlibsse-ng
    spdlog::spdlog
    fmt::fmt
)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    SKSE_SUPPORT_XSE
    UNICODE
    _UNICODE
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    SUFFIX ".dll"
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)
