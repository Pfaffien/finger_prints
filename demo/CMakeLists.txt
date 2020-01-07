cmake_minimum_required (VERSION 2.8.11)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SRC_DIR ../src)

add_executable(exe test.cpp ${SRC_DIR}/image.cpp)
# target_link_libraries(exe
#     PUBLIC
#     libFingerPrint
# )
target_include_directories(exe PUBLIC src)
target_link_libraries( exe ${OpenCV_LIBS} )
