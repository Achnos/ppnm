cmake_minimum_required(VERSION 3.15)
project(minimization)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(10-artificial-neural-networks
        CMakeLists.txt
        main.c
        makefile
        neuralnetwork.c neuralnetwork.h
        minimization.c
        minimization.h
        utilities.c
        utilities.h
        input2Array.c
        input2Array.h
        )

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(10-artificial-neural-networks GSL::gsl GSL::gslcblas)