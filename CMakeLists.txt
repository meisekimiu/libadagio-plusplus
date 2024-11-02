cmake_minimum_required(VERSION 3.25)
project(gl-adagio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/literals/*.cpp" "${CMAKE_SOURCE_DIR}/src/input/*.cpp" "${CMAKE_SOURCE_DIR}/src/math/*.cpp" "${CMAKE_SOURCE_DIR}/src/event/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/animation/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/audio/*.cpp" "${CMAKE_SOURCE_DIR}/src/graphics/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/state/*.cpp" "${CMAKE_SOURCE_DIR}/src/backends/**/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/game/systems/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/game/components/**/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/game/states/*.cpp" "${CMAKE_SOURCE_DIR}/src/game/*.cpp")
file(GLOB_RECURSE TESTS
        "${CMAKE_SOURCE_DIR}/src/literals/*.cpp" "${CMAKE_SOURCE_DIR}/test/literals/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/input/*.cpp" "${CMAKE_SOURCE_DIR}/test/input/**/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/math/*.cpp" "${CMAKE_SOURCE_DIR}/test/math/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/animation/*.cpp" "${CMAKE_SOURCE_DIR}/test/animation/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/audio/*.cpp" "${CMAKE_SOURCE_DIR}/test/audio/**/*.cpp" "${CMAKE_SOURCE_DIR}/src/game/factories/*.cpp" "${CMAKE_SOURCE_DIR}/src/game/systems/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/game/components/**/*.cpp"
        "${CMAKE_SOURCE_DIR}/test/game/**/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/graphics/*.cpp" "${CMAKE_SOURCE_DIR}/test/graphics/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/state/*.cpp" "${CMAKE_SOURCE_DIR}/test/state/**/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/event/*.cpp" "${CMAKE_SOURCE_DIR}/test/event/*.cpp"
        "${CMAKE_SOURCE_DIR}/test/*.cpp")
file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Raylib include
# This is temporary; eventually raylib will not be included in this engine
# Ideally we would use git submodules like we're using with Catch, but... again, this is just a
# stopover until we have fully removed raylib from the equation.
# This is sourced from: https://github.com/SasLuca/raylib-cmake-template/blob/master/CMakeLists.txt
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "5.0"
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.3
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(SDL2)
set(BUILD_SHARED_LIBS FALSE)

include_directories(${SDL2_SOURCE_DIR}/include)
include_directories(third_party/soloud/include)
add_subdirectory(third_party/soloud/contrib)
add_subdirectory(third_party/entt)
add_subdirectory(third_party/Catch2)
add_executable(adagio_test ${TESTS})
target_link_libraries(adagio_test PRIVATE Catch2::Catch2 raylib EnTT::EnTT)

add_executable(adagio ${SOURCES})
if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_compile_options(adagio PUBLIC "-fexceptions")
    set_target_properties(adagio
            PROPERTIES SUFFIX ".html"
            LINK_FLAGS " --bind -fexceptions -s STACK_SIZE=4194304 -s WASM=1 -s MIN_WEBGL_VERSION=1 -s ABORT_ON_WASM_EXCEPTIONS=0 -g2 -s USE_GLFW=3 -s ASYNCIFY -s USE_SDL=0 -O3 --embed-file \"${CMAKE_SOURCE_DIR}/assets@assets\"")
endif()
target_link_libraries(adagio soloud raylib EnTT::EnTT SDL2::SDL2)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/third_party/Catch2/contrib)
include(CTest)
include(Catch)
catch_discover_tests(adagio_test)
