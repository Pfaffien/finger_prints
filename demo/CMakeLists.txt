cmake_minimum_required (VERSION 2.8.11)

add_executable(exe main.cpp)
target_link_libraries(exe
    PUBLIC
    libFingerPrint
)
target_include_directories(exe PUBLIC src)