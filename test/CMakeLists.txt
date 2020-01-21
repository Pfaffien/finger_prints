# Add this line to the CMakeLists.txt containing tests
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(SRC_DIR ../src)

add_executable(tests main_tests.cpp ${SRC_DIR}/image.cpp)

target_include_directories(tests PUBLIC src test)

target_link_libraries(tests gtest ${OpenCV_LIBS} libFingerPrint)

add_test(NAME tests
    COMMAND tests
)