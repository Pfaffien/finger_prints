cmake_minimum_required (VERSION 2.8.11)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SRC_DIR ../src)
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)

#add_executable(symmetries test_symmetries.cpp ${SRC_FILES})
#add_executable(rectangles test_rectangles.cpp ${SRC_FILES})
#add_executable(starter3 test_starter3.cpp ${SRC_FILES})
add_executable(main1 test_main1.cpp ${SRC_FILES})
add_executable(rot test_starter2.cpp ${SRC_DIR}/image.cpp ${SRC_DIR}/main1.cpp)
add_executable(main2 test_main2.cpp ${SRC_DIR}/image.cpp ${SRC_DIR}/main1.cpp)

#target_include_directories(symmetries PUBLIC src)
#target_include_directories(rectangles PUBLIC src)
target_include_directories(main1 PUBLIC src)
#target_include_directories(starter3 PUBLIC src)
target_include_directories(rot PUBLIC src)
target_include_directories(main2 PUBLIC src)

target_link_libraries( main1 ${OpenCV_LIBS} libFingerPrint)
#target_link_libraries( symmetries ${OpenCV_LIBS} libFingerPrint)
#target_link_libraries( rectangles ${OpenCV_LIBS} libFingerPrint)
#target_link_libraries( starter3 ${OpenCV_LIBS} libFingerPrint)
target_link_libraries( rot ${OpenCV_LIBS} libFingerPrint)
target_link_libraries( main2 ${OpenCV_LIBS} libFingerPrint)
