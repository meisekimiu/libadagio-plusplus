cmake_minimum_required(VERSION 3.25)
project(gl-adagio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/audio/*.cpp" "${CMAKE_SOURCE_DIR}/src/graphics/*.cpp" "${CMAKE_SOURCE_DIR}/src/state/*.cpp" "${CMAKE_SOURCE_DIR}/src/game/systems/*.cpp" "${CMAKE_SOURCE_DIR}/src/game/states/*.cpp" "${CMAKE_SOURCE_DIR}/src/game/*.cpp")
file(GLOB_RECURSE TESTS "${CMAKE_SOURCE_DIR}/src/audio/*.cpp" "${CMAKE_SOURCE_DIR}/test/audio/**/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/graphics/*.cpp" "${CMAKE_SOURCE_DIR}/test/graphics/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/state/*.cpp" "${CMAKE_SOURCE_DIR}/test/state/**/*.cpp"
        "${CMAKE_SOURCE_DIR}/test/*.cpp")
file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

add_executable(game ${SOURCES})
target_link_libraries(game raylib)
include_directories(/usr/include/entt)

add_executable(game_test ${TESTS})
find_package(Catch2 REQUIRED)
target_link_libraries(game_test Catch2::Catch2 raylib)
include(CTest)
include(Catch)
catch_discover_tests(game_test)
