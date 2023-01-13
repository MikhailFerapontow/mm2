cmake_minimum_required(VERSION 3.25.0-rc2 FATAL_ERROR)

project(lab1 LANGUAGES CXX)

file(
  GLOB
  SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*
)

add_executable(
  lab1
  ${SOURCES}
)

find_package(Boost REQUIRED COMPONENTS ALL)

target_include_directories(
  lab1 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
