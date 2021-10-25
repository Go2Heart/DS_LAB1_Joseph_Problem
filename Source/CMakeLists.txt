cmake_minimum_required(VERSION 3.20)
project (lab_1)

set(CMAKE_CXX_STANDARD 98)

add_executable(lab_1
        ListByArray.cpp
        ListByArray.h
        ListByLink.cpp
        ListByLink.h
        main.cpp
        ResultPackage.cpp        
        ResultPackage.h)