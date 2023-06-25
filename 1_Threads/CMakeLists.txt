cmake_minimum_required(VERSION 3.16)

project(threads)

set(SOURCES
    src/thread_main.c
    src/thread_functions.c
    )

add_executable(threads ${SOURCES})

target_include_directories(threads PRIVATE include/)

target_link_libraries(threads LINK_PUBLIC Common pthread)

set_target_properties(threads PROPERTIES OUTPUT_NAME threads) # change output name and location