cmake_minimum_required(VERSION 3.10)
project(RayTracing)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(RayTracing main.cpp header/ImageWriter.h header/Point.h header/Vector.h src/SceneReader.cpp header/SceneReader.h src/Logger.cpp header/Logger.h header/Material.h src/Triangle.cpp header/Triangle.h src/Point.cpp src/Ray.cpp header/Ray.h src/ImageWriter.cpp)