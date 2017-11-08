cmake_minimum_required(VERSION 3.2.2)
project(stantz)

########################
# Executable
########################

set(COMMON_SOURCES
  src/Platform/Filesystem.h
)

if(WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DUNICODE)
  add_compile_options(/std:c++latest)
  add_compile_options(/W4)

  set(PLATFORM_SOURCES 
    src/Platform/Windows/Win32Environment.cpp
    src/Platform/Windows/Win32Filesystem.cpp
    src/Platform/Windows/Win32Filesystem.h
    src/Platform/Windows/Win32Graphics.cpp 
  )

  set(PLATFORM_MAIN
    src/Platform/Windows/Win32Main.cpp  
  )

  set(PLATFORM_OPTIONS 
    WIN32
  )
elseif(APPLE)
  add_definitions(-std=c++1z)

  set(PLATFORM_SOURCES
    src/Platform/OSX/OSXFilesystem.h
    src/Platform/OSX/OSXFilesystem.mm
  )

  set(PLATFORM_MAIN
    src/Platform/OSX/OSXMain.cpp  
  )

  find_library(OSX_FOUNDATION_LIBRARY CoreFoundation)
  set(PLATFORM_LIBS 
    ${OSX_FOUNDATION_LIBRARY}
  )
endif()

add_executable(Stantz
  ${PLATFORM_OPTIONS}
  ${PLATFORM_MAIN}
  ${PLATFORM_SOURCES}
  ${COMMON_SOURCES}
)

#common dependencies
find_package(OpenGL REQUIRED)
target_link_libraries(Stantz ${OPENGL_LIBRARIES})

#platform dependencies
target_link_libraries(Stantz ${PLATFORM_LIBS})

########################
# Unit Tests
########################

set(CATCH_INCLUDE_DIR ext/include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_SOURCES
  test/Main.cpp
)

add_executable(Tests 
  ${TEST_SOURCES}
  ${PLATFORM_SOURCES}
  ${COMMON_SOURCES}
)

#common dependencies
find_package(OpenGL REQUIRED)
target_link_libraries(Tests ${OPENGL_LIBRARIES})
target_link_libraries(Tests Catch)

#platform dependencies
target_link_libraries(Tests ${PLATFORM_LIBS})

# Test data 
file(COPY test/Data DESTINATION ./)