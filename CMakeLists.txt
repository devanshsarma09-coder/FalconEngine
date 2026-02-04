cmake_minimum_required(VERSION 3.24)
project(FalconEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force Skyrim AE
set(SKYRIM_AE ON CACHE BOOL "" FORCE)

# 1. FMT
message(STATUS "Configuring FMT from: ${FMT_PATH}")
add_subdirectory(${FMT_PATH} ${CMAKE_BINARY_DIR}/fmt EXCLUDE_FROM_ALL)
set(fmt_DIR ${CMAKE_BINARY_DIR}/fmt CACHE PATH "" FORCE)

# 2. SPDLOG
message(STATUS "Configuring SPDLOG from: ${SPDLOG_PATH}")
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)
add_subdirectory(${SPDLOG_PATH} ${CMAKE_BINARY_DIR}/spdlog EXCLUDE_FROM_ALL)
set(spdlog_DIR ${CMAKE_BINARY_DIR}/spdlog CACHE PATH "" FORCE)

# 3. TRICK COMMONLIB: Define the targets it wants so find_package doesn't run
# We create "alias" targets so CommonLib thinks it found the packages
if(NOT TARGET spdlog::spdlog)
    add_library(spdlog::spdlog ALIAS spdlog)
endif()
if(NOT TARGET fmt::fmt)
    add_library(fmt::fmt ALIAS fmt)
endif()

# We also need to mock find_package for CommonLib
set(spdlog_FOUND TRUE)
set(fmt_FOUND TRUE)

# 4. CommonLibSSE-NG
message(STATUS "Configuring CommonLib from: ${COMMONLIB_PATH}")
add_subdirectory(${COMMONLIB_PATH} ${CMAKE_BINARY_DIR}/commonlib EXCLUDE_FROM_ALL)

add_library(${PROJECT_NAME} SHARED
    "src/Main.cpp"
    "src/Hooks.cpp"
    "src/Papyrus.cpp"
    "src/MovementHandler.cpp"
    "src/InputHandler.cpp"
    "src/AIPathing.cpp"
)

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
