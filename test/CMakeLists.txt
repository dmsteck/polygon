add_executable(boost_polygon-test segfault_test.cpp)
target_link_libraries(boost_polygon-test boost_polygon)

add_test(boost_polygon-test boost_polygon-test)
