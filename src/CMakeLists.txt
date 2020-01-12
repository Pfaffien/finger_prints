# Create new project
project (libFingerPrint)

set(SRC_DIR ../src)

# Create variable containing all the CXX sources
set(SOURCES
    ${SRC_DIR}/image.cpp
)

# Add all the sources to the project
add_library(${PROJECT_NAME} ${SOURCES})
