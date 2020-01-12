# Add this line to the CMakeLists.txt containing tests
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(SRC_DIR ../src)

add_executable(all main_tests.cpp ${SRC_DIR}/image.cpp)

target_include_directories(all PUBLIC src test)

target_link_libraries(all gtest ${OpenCV_LIBS} libFingerPrint)

add_test(NAME all
    COMMAND all
)

# add_executable(test_getters test_getters.cpp ${SRC_DIR}/image.cpp)
# add_executable(test_difference test_difference.cpp ${SRC_DIR}/image.cpp)

# target_include_directories(test_getters PUBLIC src test)
# target_include_directories(test_difference PUBLIC src test)

# target_link_libraries(test_getters gtest ${OpenCV_LIBS}) libFingerPrint)
# target_link_libraries(test_difference gtest ${OpenCV_LIBS} libFingerPrint)

# add_test (NAME getter
#     COMMAND test_getters
# )

# add_test(NAME difference
#     COMMAND test_difference
# )
