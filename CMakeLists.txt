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

add_library(optimus-cpp
  src/optimus.h
  src/optimus.cpp
  src/millerrabin.h
  src/millerrabin.cpp
)

if (BUILD_EXAMPLE)
  add_executable(optimus-cpp-example
    example/main.cpp
  )
  target_link_libraries(optimus-cpp-example PRIVATE optimus-cpp)
endif()

if (BUILD_SHARED_LIBS)
  #install(TARGETS optimus-cpp.dll DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  install(TARGETS optimus-cpp DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
else()
  install(TARGETS optimus-cpp DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()
install(FILES src/optimus.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
