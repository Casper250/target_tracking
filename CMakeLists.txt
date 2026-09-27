cmake_minimum_required(VERSION 3.16)

project(TargetTracking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 REQUIRED)

add_executable(calculation
    src/main.cpp
    src/Gaussian.cpp
    src/DynMod.cpp
    src/SenMod.cpp
    src/Target.cpp
)

target_link_libraries(
    calculation PRIVATE Eigen3::Eigen
)

target_include_directories(calculation PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)