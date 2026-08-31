cmake_minimum_required(VERSION 3.20)

project(TurboLNX
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(turbolnx
    src/main.cpp
    src/cpu.cpp
    src/fan.cpp
    src/flags.cpp
    src/memory.cpp
    src/nvidia.cpp
    src/ui.cpp
)

target_include_directories(turbolnx
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(turbolnx
    PRIVATE
        nvidia-ml
)

