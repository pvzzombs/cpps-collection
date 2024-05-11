cmake_minimum_required(VERSION 3.5.0)

project(cpps-collection-combinatorics)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(add_cpp_file PROBLEM_NAME CPP_FILE_NAME)
  add_executable(${PROBLEM_NAME} ${CPP_FILE_NAME})
endfunction()

add_cpp_file(combinations combinations.cpp)
add_cpp_file(minimum_genetic_mutation minimum_genetic_mutation.cpp)
add_cpp_file(permutations permutations.cpp)
add_cpp_file(lcssubsqc lcssubsqc.cpp)
