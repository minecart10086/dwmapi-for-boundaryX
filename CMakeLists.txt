cmake_minimum_required(VERSION 3.22)
project(dwmapi-proxy-generator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Windows specific settings
if(WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
endif()

# Add dependencies
add_subdirectory(deps/Constructs)
add_subdirectory(deps/String)
add_subdirectory(deps/Helpers)
add_subdirectory(deps/File)

# Add proxy_generator tool
add_subdirectory(proxy_generator)

# Add proxy DLL target
add_subdirectory(proxy)
