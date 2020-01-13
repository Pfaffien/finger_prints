cmake_minimum_required (VERSION 2.8.11)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SRC_DIR ../src)

add_executable(symmetries test_symmetries.cpp ${SRC_DIR}/image.cpp)
add_executable(rectangles test_rectangles.cpp ${SRC_DIR}/image.cpp)
add_executable(starter3 test_starter3.cpp ${SRC_DIR}/image.cpp ${SRC_DIR}/starter3.cpp)
# target_link_libraries(exe
#     PUBLIC
#     libFingerPrint
# )
target_include_directories(symmetries PUBLIC src)
target_include_directories(rectangles PUBLIC src)
target_include_directories(starter3 PUBLIC src)
target_link_libraries( symmetries ${OpenCV_LIBS} )
target_link_libraries( rectangles ${OpenCV_LIBS} )
target_link_libraries( starter3 ${OpenCV_LIBS} )
