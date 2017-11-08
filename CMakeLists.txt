cmake_minimum_required(VERSION 3.2.2)
project(stantz)

find_package(OpenGL REQUIRED)
find_package(Git REQUIRED)

if(MSVC) 
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DUNICODE)
  add_compile_options(/std:c++latest)
  add_compile_options(/W4)
else() 
  # add_compile_options(-Wall -Wextra -Wpedantic)
endif() 

add_executable(Stantz WIN32
  src/Platform/Windows/graphics.cpp
  src/Platform/Windows/main.cpp
  src/Platform/Windows/Win32Environment.cpp
  src/Platform/Windows/Win32Filesystem.cpp
  src/Platform/Windows/Win32Filesystem.h
  src/Platform/Filesystem.h
  src/Rendering/Image.h
  src/Sound/Sound.h
)

target_link_libraries(Stantz ${OPENGL_LIBRARIES})

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Make test executable
set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test/Main.cpp)
add_executable(tests 
  src/Platform/Windows/Win32Filesystem.cpp
  ${TEST_SOURCES}
)
target_link_libraries(tests Catch)

# Test data 
file(COPY test/Data DESTINATION Debug/)
