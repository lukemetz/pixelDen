cmake_minimum_required (VERSION 2.6)
project (pixelDen)

aux_source_directory(. FILES)

add_executable (basicTest ${FILES})

add_definitions("-g")
add_definitions("-Wall")
add_definitions("-std=c++11")

target_link_libraries(basicTest GL)
target_link_libraries(basicTest glfw)
target_link_libraries(basicTest GLEW)


