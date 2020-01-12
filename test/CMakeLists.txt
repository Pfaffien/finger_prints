# Add this line to the CMakeLists.txt containing tests
include_directories(include)

add_executable(test_gtest test_gtest.cpp ../src/image.cpp)
target_link_libraries(test_gtest gtest)# libFingerPrint)

add_test (NAME gtest
    COMMAND test_gtest
)
