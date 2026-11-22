cmake_minimum_required(VERSION 3.10)
project(asst1_parallel CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/O2 /EHsc)
    add_compile_options(/D_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-O3 -pthread)
endif()

add_executable(mandelbrot_threads 
    prog1_mandelbrot_threads/main.cpp
    prog1_mandelbrot_threads/mandelbrotSerial.cpp
    prog1_mandelbrot_threads/mandelbrotThread.cpp
)

# Указываем, где искать заголовочные файлы (.h)
target_include_directories(mandelbrot_threads PRIVATE 
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/prog1_mandelbrot_threads
)

if(NOT MSVC)
    target_link_libraries(mandelbrot_threads pthread)
endif()