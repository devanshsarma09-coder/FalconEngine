cmake_minimum_required(VERSION 3.24)
project(FalconEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This must come BEFORE find_package
set(VCPKG_TARGET_TRIPLET "x64-windows-static-md" CACHE STRING "")

find_package(commonlibsse-ng CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED
    "src/Main.cpp"
    "src/Hooks.cpp"
    "src/Papyrus.cpp"
    "src/MovementHandler.cpp"
    "src/InputHandler.cpp"
    "src/AIPathing.cpp"
)

target_link_libraries(${PROJECT_NAME} PRIVATE commonlibsse-ng::commonlibsse-ng)

# Ensure the compiler knows we are targeting Skyrim
target_compile_definitions(${PROJECT_NAME} PRIVATE SKSE_SUPPORT_XSE)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    SUFFIX ".dll"
)
