# Create new project
project (libFingerPrint)

set(SRC_DIR ../src)
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)

# Create variable containing all the CXX sources
set(SOURCES ${SRC_FILES})

# Add all the sources to the project
add_library(${PROJECT_NAME} ${SOURCES})
