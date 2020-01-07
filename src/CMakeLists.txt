# Create new project
project (libFingerPrint)

# Create variable containing all the CXX sources
set(SOURCES
    src/file1.cxx src/file2.cxx
)

# Add all the sources to the project
add_library(${PROJECT_NAME} ${SOURCES})
