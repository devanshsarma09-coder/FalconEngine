cmake_minimum_required(VERSION 3.24)
project(FalconEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

# Just point to the headers. No find_package, no complex logic.
include_directories(
    "src"
    "${COMMONLIB_PATH}/include"
    "${SPDLOG_PATH}/include"
    "${FMT_PATH}/include"
)

add_library(${PROJECT_NAME} SHARED
    "src/Main.cpp"
    "src/Hooks.cpp"
    "src/Papyrus.cpp"
    "src/MovementHandler.cpp"
    "src/InputHandler.cpp"
    "src/AIPathing.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".dll")
target_compile_definitions(${PROJECT_NAME} PRIVATE SKSE_SUPPORT_XSE UNICODE _UNICODE)
