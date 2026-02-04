cmake_minimum_required(VERSION 3.24)
project(FalconEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Ensure we don't prompt for credentials
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
    commonlibsse-ng
    GIT_REPOSITORY "https://github.com/p13373/CommonLibSSE-NG.git"
    GIT_TAG        "main"
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

# Mandatory flags for CommonLibSSE-NG to build without a package manager
set(SKYRIM_AE ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(commonlibsse-ng)

add_library(${PROJECT_NAME} SHARED
    "src/Main.cpp"
    "src/Hooks.cpp"
    "src/Papyrus.cpp"
    "src/MovementHandler.cpp"
    "src/InputHandler.cpp"
    "src/AIPathing.cpp"
)

target_link_libraries(${PROJECT_NAME} PRIVATE commonlibsse-ng::commonlibsse-ng)

# Target definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    SKSE_SUPPORT_XSE
    UNICODE
    _UNICODE
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    SUFFIX ".dll"
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)
