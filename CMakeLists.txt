cmake_minimum_required(VERSION 2.8.11)
project(FingerPrint)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#add_subdirectory(src)
#add_subdirectory(doc)
add_subdirectory(demo)

# # Download googletest while doing the configuration
# configure_file(CMakeLists.txt.in
#                googletest-download/CMakeLists.txt)
# execute_process(COMMAND ${CMAKE_COMMAND}
#   -G "${CMAKE_GENERATOR}" .
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
# execute_process(COMMAND ${CMAKE_COMMAND} --build .
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Add googletest when compiling
# add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#                  ${CMAKE_BINARY_DIR}/googletest-build)

# include_directories(${gtest_SOURCE_DIR}/include)

# add_subdirectory(test)

# enable_testing ()
