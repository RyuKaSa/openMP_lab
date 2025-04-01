cmake_minimum_required(VERSION 3.10)
project(MyOpenMPProject C)

# Find the OpenMP package.
find_package(OpenMP REQUIRED)
if(OpenMP_C_FOUND)
    message(STATUS "OpenMP found")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

# Optionally, collect common source files (if needed)
# file(GLOB COMMON_SOURCES "src/common/*.c")

# Collect all main files matching exercice_*.c in the src folder.
file(GLOB EXERCISE_FILES "src/exercice_*.c")

# For each main file, create an executable target.
foreach(ex_file ${EXERCISE_FILES})
    # Get the filename without the extension (e.g., exercice_1)
    get_filename_component(ex_name ${ex_file} NAME_WE)
    
    # Create an executable using the main file (and any common sources if needed)
    add_executable(${ex_name} ${ex_file} )
    
    # If we have common sources, append them:
    # add_executable(${ex_name} ${ex_file} ${COMMON_SOURCES})
    
    # Link OpenMP libraries for each target.
    target_link_libraries(${ex_name} PUBLIC OpenMP::OpenMP_C)
endforeach()