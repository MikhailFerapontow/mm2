cmake_minimum_required(VERSION 3.25.0-rc2 FATAL_ERROR)
project(lab2 VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS ALL)
find_package(GSL REQUIRED)

file(
  GLOB
  SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(lab2)

target_include_directories(
  lab2 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_sources(
  lab2 PRIVATE 
  ${SOURCES}
)

target_include_directories(lab2
  PRIVATE ${GSL_INCLUDE_DIRS}
)
target_link_libraries(lab2
  GSL::gsl GSL::gslcblas
)
