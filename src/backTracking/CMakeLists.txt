cmake_minimum_required(VERSION 3.5.0)

project(cpps-collection-backtracking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(add_cpp_file PROBLEM_NAME CPP_FILE_NAME)
  add_executable(${PROBLEM_NAME} ${CPP_FILE_NAME})
endfunction()

add_cpp_file(generateParenthesis generateParenthesis.cpp)
add_cpp_file(knightour knightour.cpp)
add_cpp_file(Nqueens Nqueens.cpp)
