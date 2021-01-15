cmake_minimum_required(VERSION 3.14)
project(ooplab4)

set(CMAKE_CXX_STANDARD 14)

add_executable(ooplab4
        main.cpp
        FileUtil.cpp FileUtil.h
        Matrix.cpp Matrix.h
        BigNum.cpp BigNum.h
        )