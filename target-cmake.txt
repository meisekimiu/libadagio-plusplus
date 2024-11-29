cmake_minimum_required(VERSION 3.25)
project(muffins)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/**/*.cpp")

include_directories(3rdparty/adagio/src/include)
include_directories(3rdparty/adagio/third_party/soloud/include)
add_subdirectory(3rdparty/adagio)
add_executable(muffins ${SOURCES})

file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

target_link_libraries(muffins gl-adagio soloud raylib EnTT::EnTT SDL2::SDL2)

