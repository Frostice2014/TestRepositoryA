cmake_minimum_required(VERSION 3.10)
project(TestA VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()