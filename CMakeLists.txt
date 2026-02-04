cmake_minimum_required(VERSION 3.24)
project(FalconEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if we provided a local path in the build script
if(DEFINED COMMONLIB_LOCAL_PATH)
    message(STATUS "Using local CommonLib from: ${COMMONLIB_LOCAL_PATH}")
    add_subdirectory(${COMMONLIB_LOCAL_PATH} build/_deps/commonlibsse-ng-src EXCLUDE_FROM_ALL)
else()
    # Fallback to FetchContent if building locally
    include(FetchContent)
    FetchContent_Declare(
        commonlibsse-ng
        GIT_REPOSITORY "https://github.com/CharmedBaryon/CommonLibSSE-NG?hl=en-IN"
        GIT_TAG        "main"
    )
    FetchContent_MakeAvailable(commonlibsse-ng)
endif()

# Mandatory flags
set(SKYRIM_AE ON CACHE BOOL "" FORCE)

add_library(${PROJECT_NAME} SHARED
    "src/Main.cpp"
    "src/Hooks.cpp"
    "src/Papyrus.cpp"
    "src/MovementHandler.cpp"
    "src/InputHandler.cpp"
    "src/AIPathing.cpp"
)

target_link_libraries(${PROJECT_NAME} PRIVATE commonlibsse-ng::commonlibsse-ng)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    SKSE_SUPPORT_XSE
    UNICODE
    _UNICODE
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    SUFFIX ".dll"
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)

