cmake_minimum_required(VERSION 3.20)
project(ReportStyleAnalyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(ReportStyleAnalyzer main.cpp ReportAnalyzer.cpp ReportAnalyzer.h AVL.cpp AVL.h)
