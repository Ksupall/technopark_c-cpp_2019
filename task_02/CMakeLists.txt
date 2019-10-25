add_executable(task_02 main.cpp serial_work.cpp parallel_work.cpp)

add_executable(test_02 test.cpp serial_work.cpp parallel_work.cpp)
target_link_libraries(test_02 GTest::GTest GTest::Main)
add_test(NAME Task02Tests COMMAND test_02)