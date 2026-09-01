file(GLOB_RECURSE MATH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(pesec_math SHARED ${MATH_SOURCES})

target_include_directories(pesec_math PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(pesec_math PUBLIC pesec_core)

set_target_properties(pesec_math PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        OUTPUT_NAME "pesec_math"
)