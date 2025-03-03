cmake_minimum_required(VERSION 3.10)
project(tests)

set(CMAKE_CXX_STANDARD 11)


find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
find_package(Boost REQUIRED)   

set(GTEST_ROOT /usr/local)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(tests tests.cpp)
target_link_libraries(tests ${OpenCL_LIBRARIES} ${GTEST_LIBRARIES} ${Boost_LIBRARIES} pthread)

