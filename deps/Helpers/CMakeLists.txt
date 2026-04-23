cmake_minimum_required(VERSION 3.22)
set(TARGET Helpers)
project(${TARGET})

option(${TARGET}_BUILD_SHARED "Build as a shared lib" OFF)

set(${TARGET}_Sources
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Casting.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/SysError.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Time.cpp"
        )

string(REGEX REPLACE "(.)([A-Z])" "\\1_\\2" MODULE_NAME ${TARGET})
string(TOUPPER ${MODULE_NAME} MODULE_NAME)

if (${TARGET}_BUILD_SHARED)
    message("Project: ${TARGET} (SHARED)")
    add_library(${TARGET} SHARED ${${TARGET}_Sources})
else ()
    message("Project: ${TARGET} (STATIC)")
    add_library(${TARGET} ${${TARGET}_Sources})
endif ()

# Enabling c++23 support
target_compile_features(${TARGET} PUBLIC cxx_std_23)

target_compile_definitions(${TARGET} PRIVATE
        RC_${MODULE_NAME}_EXPORTS
        $<$<NOT:$<BOOL:${${TARGET}_BUILD_SHARED}>>:
            RC_${MODULE_NAME}_BUILD_STATIC>)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add fmt dependency if not already added
if(NOT TARGET fmt)
    find_package(fmt QUIET)
    if(NOT fmt_FOUND)
        include(FetchContent)
        FetchContent_Declare(
            fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG 10.2.1
        )
        FetchContent_MakeAvailable(fmt)
    endif()
endif()

target_link_libraries(${TARGET} PUBLIC String fmt::fmt)
