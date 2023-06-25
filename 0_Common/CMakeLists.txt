set(LIBRARY_SOURCES
    src/math_functions_64_bit.c
    src/utilities.c
    src/number_converter.c
    src/file_io.c
    )

add_library(Common ${LIBRARY_SOURCES})

target_include_directories(Common PUBLIC include/)