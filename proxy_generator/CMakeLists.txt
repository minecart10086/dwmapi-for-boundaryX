cmake_minimum_required(VERSION 3.22)

set(TARGET proxy_generator)
project(${TARGET})

add_executable(${TARGET} "main.cpp")
target_link_libraries(${TARGET} PRIVATE Constructs File)
target_compile_definitions(${TARGET} PRIVATE RC_FILE_BUILD_STATIC)

# Windows specific libraries
if(WIN32)
    target_link_libraries(${TARGET} PRIVATE imagehlp)
endif()
