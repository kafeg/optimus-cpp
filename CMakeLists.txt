cmake_minimum_required(VERSION 3.14)

project(optimus-cpp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

option(BUILD_SHARED_LIBS OFF)
option(BUILD_EXAMPLE ON)

if(BUILD_SHARED_LIBS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

add_library(optimus-cpp
  src/optimus.h
  src/optimus.cpp
)

if (BUILD_SHARED_LIBS)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/optimus-cpp.dll DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/optimus-cpp.lib DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
else()
  install(TARGETS optimus-cpp DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()
install(FILES src/optimus.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

if (BUILD_EXAMPLE)
  add_executable(optimus-cpp-example
    example/main.cpp
  )
  target_link_libraries(optimus-cpp-example PRIVATE optimus-cpp)
endif()
