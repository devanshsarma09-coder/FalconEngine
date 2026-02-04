cmake_minimum_required(VERSION 3.24)
project(FalconEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force Skyrim AE support and tell CommonLib to fetch its own deps
set(SKYRIM_AE ON CACHE BOOL "" FORCE)
set(COMMONLIB_EXTERNAL_DEPENDENCIES ON CACHE BOOL "" FORCE)

if(DEFINED COMMONLIB_LOCAL_PATH)
    message(STATUS "Using local CommonLib from: ${COMMONLIB_LOCAL_PATH}")
    # EXCLUDE_FROM_ALL prevents building CommonLib tests/samples
    add_subdirectory(${COMMONLIB_LOCAL_PATH} build/_deps/commonlibsse-ng-src EXCLUDE_FROM_ALL)
else()
    include(FetchContent)
    FetchContent_Declare(
        commonlibsse-ng
        GIT_REPOSITORY "https://github.com/CharmedBaryon/CommonLibSSE-NG.git"
        GIT_TAG        "main"
    )
    FetchContent_MakeAvailable(commonlibsse-ng)
endif()

add_library(${PROJECT_NAME} SHARED
    "src/Main.cpp"
    "src/Hooks.cpp"
    "src/Papyrus.cpp"
    "src/MovementHandler.cpp"
    "src/InputHandler.cpp"
    "src/AIPathing.cpp"
)

# Link the library provided by CharmedBaryon
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
