cmake_minimum_required(VERSION 3.5.0)

project(cpps-collection-graph)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(add_cpp_file PROBLEM_NAME CPP_FILE_NAME)
  add_executable(${PROBLEM_NAME} ${CPP_FILE_NAME})
endfunction()

add_cpp_file(allgraph01 allgraph01.cpp)
add_cpp_file(dgraph01 dgraph01.cpp)
add_cpp_file(dgraph02 dgraph02.cpp)
add_cpp_file(graph01 graph01.cpp)
add_cpp_file(graph02 graph02.cpp)
add_cpp_file(graph03 graph03.cpp)
add_cpp_file(graph04 graph04.cpp)
