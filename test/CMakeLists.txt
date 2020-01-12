# Add this line to the CMakeLists.txt containing tests
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(SRC_DIR ../src)

add_executable(test_gtest test_gtest.cpp ${SRC_DIR}/image.cpp)
target_include_directories(test_gtest PUBLIC src test)
target_link_libraries(test_gtest gtest ${OpenCV_LIBS})# libFingerPrint)

add_test (NAME gtest
    COMMAND test_gtest
)
