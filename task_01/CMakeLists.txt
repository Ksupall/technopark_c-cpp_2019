add_executable(task_01 main.c struct_io.c)

add_executable(test_01 test.cpp)
target_link_libraries(test_01 GTest::GTest GTest::Main)
add_test(NAME Task01Tests COMMAND test_01)