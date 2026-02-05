cmake_minimum_required(VERSION 3.24)
project(FalconEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SKYRIM_AE ON CACHE BOOL "" FORCE)
# Try harder to kill tests
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(COMMONLIB_BUILD_TESTS OFF CACHE BOOL "" FORCE)

# Convert paths
file(TO_CMAKE_PATH "${FMT_PATH}" SAFE_FMT_PATH)
file(TO_CMAKE_PATH "${SPDLOG_PATH}" SAFE_SPDLOG_PATH)
file(TO_CMAKE_PATH "${COMMONLIB_PATH}" SAFE_COMMONLIB_PATH)

# 1. FMT
message(STATUS "Pre-configuring FMT from: ${SAFE_FMT_PATH}")
add_subdirectory(${SAFE_FMT_PATH} ${CMAKE_BINARY_DIR}/fmt EXCLUDE_FROM_ALL)

# 2. SPDLOG
message(STATUS "Pre-configuring SPDLOG from: ${SAFE_SPDLOG_PATH}")
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)
add_subdirectory(${SAFE_SPDLOG_PATH} ${CMAKE_BINARY_DIR}/spdlog EXCLUDE_FROM_ALL)

# 3. MOCKING find_package (Now with Catch2!)
file(WRITE "${CMAKE_BINARY_DIR}/spdlog/spdlogConfig.cmake" "set(spdlog_FOUND TRUE)")
file(WRITE "${CMAKE_BINARY_DIR}/fmt/fmtConfig.cmake" "set(fmt_FOUND TRUE)")
# This is the new line that fixes your error:
file(WRITE "${CMAKE_BINARY_DIR}/Catch2/Catch2Config.cmake" "set(Catch2_FOUND TRUE)")

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/spdlog")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/fmt")
# Add the fake Catch2 path
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/Catch2")

# 4. CommonLibSSE-NG
message(STATUS "Configuring CommonLib from: ${SAFE_COMMONLIB_PATH}")
set(COMMONLIB_EXTERNAL_DEPENDENCIES OFF CACHE BOOL "" FORCE) 
add_subdirectory(${SAFE_COMMONLIB_PATH} ${CMAKE_BINARY_DIR}/commonlib EXCLUDE_FROM_ALL)

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
