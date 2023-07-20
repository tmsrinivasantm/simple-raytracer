cmake_minimum_required(VERSION 3.25.1)

project(raytracer)

file(GLOB helloworld_SRC "src/*.cpp")

add_executable(raytracer ${helloworld_SRC})

include_directories(raytracer PRIVATE includes)

#structures
add_subdirectory(libs/structures)
target_link_libraries(raytracer structures)

#utilities
add_subdirectory(libs/utilities)
target_link_libraries(raytracer utilities)

#materials
add_subdirectory(libs/materials)
target_link_libraries(raytracer materials)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(raytracer OpenMP::OpenMP_CXX)
endif()