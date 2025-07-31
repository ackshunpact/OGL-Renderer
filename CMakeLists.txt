cmake_minimum_required(VERSION 3.31)
project(ducky)
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()
find_package(fmt CONFIG REQUIRED)
include_directories(${FMT_INCLUDE_DIR})

find_package(glm CONFIG REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

find_package(glfw3 CONFIG REQUIRED)

find_package(tinyobjloader CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(ducky main.cpp ${CMAKE_SOURCE_DIR}/libraries/glad/src/glad.c
        src/Camera.cpp
        src/Camera.h
        src/Renderer.cpp
        src/Renderer.h
        src/Definitions.h
        src/Scene.cpp
        src/Scene.h
        src/OBJMesh.cpp
        src/OBJMesh.h
        src/Vertex.h
        src/PerspectiveProjectionInfo.h
        src/Window.cpp
        src/Window.h
        src/Shader.cpp
        src/Shader.h)
target_link_libraries(ducky PRIVATE fmt::fmt glm::glm glfw ${CMAKE_SOURCE_DIR}/libraries/glad/include/glad/glad.h tinyobjloader::tinyobjloader)
