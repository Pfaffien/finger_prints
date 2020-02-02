cmake_minimum_required (VERSION 2.8.11)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SRC_DIR ../src)
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)


add_executable(rectangles test_rectangles.cpp ${SRC_FILES})
target_include_directories(rectangles PUBLIC src)
target_link_libraries(rectangles ${OpenCV_LIBS} libFingerPrint)

add_executable(symmetries test_symmetries.cpp ${SRC_FILES})
target_include_directories(symmetries PUBLIC src)
target_link_libraries(symmetries ${OpenCV_LIBS} libFingerPrint)

add_executable(pressure test_pressure.cpp ${SRC_FILES})
target_include_directories(pressure PUBLIC src)
target_link_libraries(pressure ${OpenCV_LIBS} libFingerPrint)

add_executable(rotations test_rotations.cpp ${SRC_FILES})
target_include_directories(rotations PUBLIC src)
target_link_libraries(rotations ${OpenCV_LIBS} libFingerPrint)

add_executable(elasticity test_elasticity.cpp ${SRC_DIR}/image.cpp)
target_include_directories(elasticity PUBLIC src)
target_link_libraries(elasticity ${OpenCV_LIBS} libFingerPrint)

add_executable(linear_filtering test_linear_filtering.cpp ${SRC_FILES})
target_include_directories(linear_filtering PUBLIC src)
target_link_libraries(linear_filtering ${OpenCV_LIBS} libFingerPrint)

add_executable(morphological_filtering test_morphological_filtering.cpp ${SRC_FILES})
target_include_directories(morphological_filtering PUBLIC src)
target_link_libraries(morphological_filtering ${OpenCV_LIBS} libFingerPrint)

add_executable(translation test_translations.cpp ${SRC_FILES})
target_include_directories(translation PUBLIC src)
target_link_libraries(translation ${OpenCV_LIBS} libFingerPrint)

add_executable(optimization test_optimization.cpp ${SRC_FILES})
target_include_directories(optimization PUBLIC src)
target_link_libraries(optimization ${OpenCV_LIBS} libFingerPrint)

#add_executable(demo demo.cpp ${SRC_FILES})
#target_include_directories(demo PUBLIC src)
#target_link_libraries(demo ${OPENCV_LIBS} libFingerPrint)
