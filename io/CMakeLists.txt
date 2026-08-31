file(GLOB_RECURSE IO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(pesec_io SHARED ${IO_SOURCES})

target_include_directories(pesec_io PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(pesec_io PUBLIC pesec_core)

set_target_properties(pesec_io PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        OUTPUT_NAME "pesec_io"
)