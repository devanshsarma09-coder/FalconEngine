cmake_minimum_required(VERSION 3.24)
project(FalconEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Automatically download CommonLibSSE-NG
FetchContent_Declare(
    commonlibsse-ng
    GIT_REPOSITORY https://github.com/p13373/CommonLibSSE-NG.git
    GIT_TAG        main
)

# This flag is required to make CommonLib build correctly without vcpkg
set(SKYRIM_AE ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(commonlibsse-ng)

add_library(${PROJECT_NAME} SHARED
    "src/Main.cpp"
    "src/Hooks.cpp"
    "src/Papyrus.cpp"
    "src/MovementHandler.cpp"
    "src/InputHandler.cpp"
    "src/AIPathing.cpp"
)

# Link the downloaded library
target_link_libraries(${PROJECT_NAME} PRIVATE commonlibsse-ng::commonlibsse-ng)

# Ensure the DLL suffix is correct
set_target_properties(${PROJECT_NAME} PROPERTIES 
    SUFFIX ".dll"
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)
