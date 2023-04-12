add_executable (AdminTest AdminTest.cpp)
target_link_libraries (AdminTest PRIVATE Catch2::Catch2WithMain isonata-server isonata-admin)
add_test (NAME AdminTest COMMAND ./AdminTest)
