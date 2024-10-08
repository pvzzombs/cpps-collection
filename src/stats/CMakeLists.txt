cmake_minimum_required(VERSION 3.5.0)

project(cpps-collection-stats)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(add_cpp_file PROBLEM_NAME CPP_FILE_NAME)
  add_executable(${PROBLEM_NAME} ${CPP_FILE_NAME})
  target_include_directories(${PROBLEM_NAME} PRIVATE "C:/usr/local/include" )
endfunction()

add_cpp_file(neuralNetwork3Layer neuralNetwork3Layer.cpp)
