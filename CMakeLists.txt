cmake_minimum_required(VERSION 3.16)

project(
    Thread_Exercises
    LANGUAGES "C"
    DESCRIPTION "Unix Threading Exercises"
)

include(threading.cmake)

include_directories(0_Common/include)

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/0_Common/CMakeLists.txt")
    add_subdirectory(0_Common)
endif()

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/1_Threads/CMakeLists.txt")
    add_subdirectory(1_Threads)
endif()

# EOF
