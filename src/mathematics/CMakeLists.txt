cmake_minimum_required(VERSION 3.5.0)

project(cpps-collection-mathematics)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(add_cpp_file PROBLEM_NAME CPP_FILE_NAME)
  add_executable(${PROBLEM_NAME} ${CPP_FILE_NAME})
endfunction()

add_cpp_file(bisect bisect.cpp)
add_cpp_file(newton_method newton_method.cpp)
add_cpp_file(polynomial polynomial.cpp)
add_cpp_file(seq_solver seq_solver.cpp)
add_cpp_file(seq1 seq1.cpp)
