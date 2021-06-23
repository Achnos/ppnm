cmake_minimum_required(VERSION 3.15)
project(interpolation)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(1-interpolation
        CMakeLists.txt
        main.c
        makefile
        cubicSpline.c cubicSpline.h
        linSpline.c linSpline.h
        quadSpline.c quadSpline.h
        utilities.c utilities.h
        )

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(1-interpolation GSL::gsl GSL::gslcblas)