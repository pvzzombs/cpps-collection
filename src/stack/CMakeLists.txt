cmake_minimum_required(VERSION 3.5.0)

project(cpps-collection-stack)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(add_cpp_file PROBLEM_NAME CPP_FILE_NAME)
  add_executable(${PROBLEM_NAME} ${CPP_FILE_NAME})
endfunction()

add_cpp_file(infix_to_postfix infix_to_postfix.cpp)
add_cpp_file(infixtopostfix2 infixtopostfix2.cxx)
add_cpp_file(stack stack.cpp)
