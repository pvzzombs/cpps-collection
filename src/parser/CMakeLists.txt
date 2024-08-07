cmake_minimum_required(VERSION 3.5.0)

project(cpps-collection-parser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(add_cpp_file PROBLEM_NAME CPP_FILE_NAME)
  add_executable(${PROBLEM_NAME} ${CPP_FILE_NAME})
endfunction()

add_cpp_file(rdp1 rdp1.cpp)
add_cpp_file(rdp2 rdp2.cpp)
add_cpp_file(rdp3 rdp3.cpp)
add_cpp_file(arithmetic arithmetic.cpp)
