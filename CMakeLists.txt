cmake_minimum_required(VERSION 3.15)

project(DataStructuresLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# 1. Define the executable FIRST so CMake knows it exists
add_executable(main main.cpp)

target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# 2. Configure Valgrind to use the 'main' target
find_program(VALGRIND_PROGRAM valgrind)
if(VALGRIND_PROGRAM)
    message(STATUS "Valgrind found: ${VALGRIND_PROGRAM}")

    add_custom_target(valgrind
        COMMAND ${VALGRIND_PROGRAM} 
                --leak-check=full 
                --show-leak-kinds=all 
                --track-origins=yes 
                $<TARGET_FILE:main>  
        DEPENDS main                 
        COMMENT "Running Valgrind memory check on main..."
    )
else()
    message(WARNING "Valgrind not found! The 'valgrind' target will not be available.")
endif()