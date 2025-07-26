cmake_minimum_required(VERSION 3.8)
project(glad)

add_library(glad)
if(ANDROID)
target_sources(glad PRIVATE src/glad_egl.c)
endif()

target_sources(glad PRIVATE src/glad.c)

target_include_directories(glad PUBLIC include)
