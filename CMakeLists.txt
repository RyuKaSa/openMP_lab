cmake_minimum_required(VERSION 3.10)
project(MyOpenMPProject C)

# Find the OpenMP package.
find_package(OpenMP REQUIRED)
if(OpenMP_C_FOUND)
    message(STATUS "OpenMP found")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

# Collect all main files matching exercice_*.c in the src folder.
file(GLOB EXERCISE_FILES "src/exercice_*.c")

# For each main file, create an executable target.
foreach(ex_file ${EXERCISE_FILES})
    # Get the filename without the extension (e.g., exercice_1)
    get_filename_component(ex_name ${ex_file} NAME_WE)
    
    add_executable(${ex_name} ${ex_file} )
    
    # Link OpenMP libraries for each target.
    target_link_libraries(${ex_name} PUBLIC OpenMP::OpenMP_C)
endforeach()