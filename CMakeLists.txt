cmake_minimum_required(VERSION 3.24)
project(FalconEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force Skyrim AE
set(SKYRIM_AE ON CACHE BOOL "" FORCE)

# 1. FMT
message(STATUS "Pre-configuring FMT from: ${FMT_PATH}")
add_subdirectory(${FMT_PATH} ${CMAKE_BINARY_DIR}/fmt EXCLUDE_FROM_ALL)
# Add FMT to the search path so find_package works
list(APPEND CMAKE_PREFIX_PATH "${FMT_PATH}")
set(fmt_DIR "${CMAKE_BINARY_DIR}/fmt" CACHE PATH "" FORCE)

# 2. SPDLOG
message(STATUS "Pre-configuring SPDLOG from: ${SPDLOG_PATH}")
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)
add_subdirectory(${SPDLOG_PATH} ${CMAKE_BINARY_DIR}/spdlog EXCLUDE_FROM_ALL)
# Add SPDLOG to the search path
list(APPEND CMAKE_PREFIX_PATH "${SPDLOG_PATH}")
set(spdlog_DIR "${CMAKE_BINARY_DIR}/spdlog" CACHE PATH "" FORCE)

# 3. MOCKING find_package
# We create a fake "spdlogConfig.cmake" so find_package(spdlog) returns success instantly
file(WRITE "${CMAKE_BINARY_DIR}/spdlog/spdlogConfig.cmake" "include_directories(\"${SPDLOG_PATH}/include\")\nadd_library(spdlog::spdlog ALIAS spdlog)")
file(WRITE "${CMAKE_BINARY_DIR}/fmt/fmtConfig.cmake" "include_directories(\"${FMT_PATH}/include\")\nadd_library(fmt::fmt ALIAS fmt)")

# Add these fake config paths to the search list
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/spdlog")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/fmt")

# 4. CommonLibSSE-NG
message(STATUS "Configuring CommonLib from: ${COMMONLIB_PATH}")
# Disable CommonLib's internal dependency search if possible
set(COMMONLIB_EXTERNAL_DEPENDENCIES OFF CACHE BOOL "" FORCE) 
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
