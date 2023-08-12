cmake_minimum_required(VERSION 3.25)
project(gl-adagio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE TESTS "${CMAKE_SOURCE_DIR}/test/*.cpp")
file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

add_executable(game ${SOURCES} src/graphics/SpriteBatch.cpp src/graphics/SpriteBatch.h src/graphics/SpriteState.cpp src/graphics/SpriteState.h src/graphics/RenderState.h src/graphics/TextState.cpp src/graphics/TextState.h src/graphics/RenderState.cpp)
target_link_libraries(game raylib)
include_directories(/usr/include/entt)

add_executable(game_test ${TESTS} src/graphics/SpriteBatch.cpp src/graphics/SpriteBatch.h src/graphics/SpriteState.cpp src/graphics/SpriteState.h src/graphics/RenderState.h)
find_package(Catch2 REQUIRED)
target_link_libraries(game_test Catch2::Catch2)
include(CTest)
include(Catch)
catch_discover_tests(game_test)
