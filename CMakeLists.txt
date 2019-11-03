cmake_minimum_required(VERSION 3.12)
project(GLAdventures CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("Depdencies: ${CONAN_LIBS}")

file(GLOB CPPS src/*.cpp)
add_executable(GLAdventures ${CPPS})
target_link_libraries(GLAdventures PUBLIC ${CONAN_LIBS})
