cmake_minimum_required(VERSION 3.25.0-rc2 FATAL_ERROR)
project(lab1 VERSION 0.1.0)


include(CTest)
enable_testing()

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

add_executable(lab1)

target_include_directories(
  lab1 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_sources(
  lab1 PRIVATE 
  ${SOURCES}
)

target_include_directories(lab1
  PRIVATE ${GSL_INCLUDE_DIRS}
)
target_link_libraries(lab1
  GSL::gsl GSL::gslcblas
)


add_executable(tma_test
  ${CMAKE_CURRENT_SOURCE_DIR}/test/test_tma.cpp
)
target_include_directories(tma_test 
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(tma_test 
  PRIVATE ${Boost_INCLUDE_DIRS}
)
target_link_libraries(tma_test 
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_RANGE_LIBRARY}
)

target_include_directories(tma_test
  PRIVATE ${GSL_INCLUDE_DIRS}
)
target_link_libraries(tma_test
  GSL::gsl GSL::gslcblas
)