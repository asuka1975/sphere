cmake_minimum_required(VERSION 3.19)
project(sphere)

set(CMAKE_CXX_STANDARD 17)

add_executable(sphere main.cpp)
target_include_directories(sphere PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glplusplus/include)
target_link_libraries(sphere GL GLEW glfw gl++)

add_subdirectory(glplusplus)

file(GLOB shaders shaders/*)
foreach(shader IN ITEMS ${shaders})
    get_filename_component(name ${shader} NAME)
    configure_file(${shader} shaders/${name} COPYONLY)
endforeach()