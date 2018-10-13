cmake_minimum_required(VERSION 3.12)
project(RayTracing)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracing main.cpp header/SceneReader.h header/ImageWriter.h header/Point.h header/Vector.h header/Triangle.h)