cmake_minimum_required(VERSION 3.8) 

project(technopark_c_c++_task_02) 

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED on) 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread") 

enable_testing() 
find_package(GTest REQUIRED) 
include_directories(${GTEST_INCLUDE_DIRS}) 

set(APP_NAME main.exe)
set(TEST_NAME test.exe)

add_library(serial_work STATIC serial_work.cpp) 
add_library(parallel_work SHARED parallel_work.cpp)

add_executable(${APP_NAME} main.cpp) 

target_link_libraries(${APP_NAME} serial_work) 
target_link_libraries(${APP_NAME} parallel_work)

add_executable(${TEST_NAME} test.cpp) 

target_link_libraries(${TEST_NAME} serial_work) 
target_link_libraries(${TEST_NAME} parallel_work) 
target_link_libraries(${TEST_NAME} GTest::GTest GTest::Main)

add_test(NAME Task02Tests COMMAND ${TEST_NAME} pthread)