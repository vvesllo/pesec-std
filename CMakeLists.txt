cmake_minimum_required(VERSION 4.3)
project(pesec_std C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        pesec
        GIT_REPOSITORY https://github.com/vvesllo/pesec.git
        GIT_TAG main
)

FetchContent_MakeAvailable(pesec)

file(GLOB_RECURSE PESEC_SOURCES
        "${pesec_SOURCE_DIR}/src/*.c"
)

add_library(pesec_core STATIC ${PESEC_SOURCES})
set_target_properties(pesec_core PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(pesec_core PUBLIC
        ${pesec_SOURCE_DIR}
)

add_subdirectory(io)
add_subdirectory(math)