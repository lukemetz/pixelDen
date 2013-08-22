cmake_minimum_required (VERSION 2.6)

project (pixelDen)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)
add_definitions("-g")
add_definitions("-Wall")
add_definitions("-std=c++11")

aux_source_directory(src/ SOURCE)
add_library(pixelDen SHARED ${SOURCE})
target_link_libraries(pixelDen GL)
target_link_libraries(pixelDen glfw)
target_link_libraries(pixelDen GLEW)

add_executable(basicTest tests/basicTest.cpp)
target_link_libraries(basicTest pixelDen)
target_link_libraries(basicTest GL)
target_link_libraries(basicTest glfw)
target_link_libraries(basicTest GLEW)


include_directories("${CMAKE_SOURCE_DIR}/thirdParty/bandit/")
include_directories("${CMAKE_SOURCE_DIR}/src/")
aux_source_directory(specs/ SPECS)
add_executable(specs ${SPECS})

target_link_libraries(specs pixelDen)
target_link_libraries(specs GL)
target_link_libraries(specs glfw)
target_link_libraries(specs GLEW)

