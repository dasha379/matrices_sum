cmake_minimum_required(VERSION 3.10)
project(tests)

set(CMAKE_CXX_STANDARD 11)


find_package(OpenCL REQUIRED)
include_directories(/usr/local/cuda/include)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(tests tests.cpp)
target_link_libraries(tests ${OpenCL_LIBRARIES} ${GTEST_LIBRARIES} pthread)

