cmake_minimum_required(VERSION 3.2)

project(practicing_threads VERSION 0.0.1 LANGUAGES C)

add_executable(cnd_mutex_example src/practicing_threads.c)

add_executable(non_atomic_example src/race_conditions_with_non_atomics.c)

