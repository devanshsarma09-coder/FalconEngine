cmake_minimum_required(VERSION 3.24)
project(FalconEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

# Direct paths to headers
include_directories(
    "src"
    "${COMMONLIB_PATH}/include"
    "${SPDLOG_PATH}/include"
    "${FMT_PATH}/include"
)

# Compile only your source files
add_library(${PROJECT_NAME} SHARED
    "src/Main.cpp"
    "src/Hooks.cpp"
    "src/Papyrus.cpp"
    "src/MovementHandler.cpp"
    "src/InputHandler.cpp"
    "src/AIPathing.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    SUFFIX ".dll"
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    SKSE_SUPPORT_XSE 
    UNICODE 
    _UNICODE
)
