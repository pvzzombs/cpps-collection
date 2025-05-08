cmake_minimum_required(VERSION 3.5.0)

project(cpps-collection-sorting)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(add_cpp_file PROBLEM_NAME CPP_FILE_NAME)
  add_executable(${PROBLEM_NAME} ${CPP_FILE_NAME})
endfunction()

add_cpp_file(bubble_sort bubble_sort.cpp)
add_cpp_file(mergeSort mergeSort.cpp)
add_cpp_file(sorting sorting.cpp)