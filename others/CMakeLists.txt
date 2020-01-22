cmake_minimum_required (VERSION 2.8.11)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SRC_DIR ../src)
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)

add_executable(data_loss_functions loss_functions.cpp ${SRC_FILES})

target_include_directories(data_loss PUBLIC src)

target_link_libraries( data_loss ${OpenCV_LIBS} libFingerPrint)