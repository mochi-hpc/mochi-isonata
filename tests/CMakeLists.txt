add_executable (AdminTest AdminTest.cpp)
target_link_libraries (AdminTest PRIVATE Catch2::Catch2WithMain isonata-server isonata-admin)
add_test (NAME AdminTest COMMAND ./AdminTest)

add_executable (ClientTest ClientTest.cpp)
target_link_libraries (ClientTest PRIVATE Catch2::Catch2WithMain isonata-server isonata-admin isonata-client)
add_test (NAME ClientTest COMMAND ./ClientTest)
