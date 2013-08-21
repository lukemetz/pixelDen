cmake_minimum_required (VERSION 2.6)

add_subdirectory("thirdParty/bandit/")

project (pixelDen)

aux_source_directory(. FILES)
add_executable (basicTest ${FILES})
add_definitions("-g")
add_definitions("-Wall")
add_definitions("-std=c++11")


include_directories("${CMAKE_SOURCE_DIR}/thirdParty/bandit/")
aux_source_directory(specs/ SPECS)
add_executable(tests ${SPECS})
add_definitions("-g")
add_definitions("-Wall")
add_definitions("-std=c++11")

target_link_libraries(basicTest GL)
target_link_libraries(basicTest glfw)
target_link_libraries(basicTest GLEW)
