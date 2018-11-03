cmake_minimum_required(VERSION 3.12)
project(RayTracing)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracing main.cpp header/ImageWriter.h header/Point.h header/Vector.h src/SceneReader.cpp header/SceneReader.h src/Logger.cpp header/Logger.h header/Material.h src/Triangle.cpp header/Triangle.h src/Point.cpp src/Ray.cpp header/Ray.h)