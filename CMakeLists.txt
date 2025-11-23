cmake_minimum_required(VERSION 3.2)

project(practicing_threads VERSION 0.0.1 LANGUAGES C)

add_executable(${PROJECT_NAME} src/practicing_threads.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/inc)
