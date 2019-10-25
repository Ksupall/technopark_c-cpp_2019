add_executable(task_02 main.cpp serial_work.cpp)

add_executable(test_01 test.cpp serial_work.cpp parallel_work.cpp)
target_link_libraries(test_01 GTest::GTest GTest::Main)
add_test(NAME Task01Tests COMMAND test_01)