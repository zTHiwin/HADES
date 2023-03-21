cmake_minimum_required(VERSION 3.26)

set(MyAppName "HADESApp")

project(MyAppName)

add_executable(${PROJECT_NAME} main.cpp)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ../../lib/Win32
                           PUBLIC ../../include
                          )

target_link_directories(${PROJECT_NAME}
                        PRIVATE ../../lib/Win32
                        PRIVATE ../../include
                       )

target_link_libraries(${PROJECT_NAME} HIMC_API)

configure_file(${CMAKE_SOURCE_DIR}/../../lib/Win32/HIMC_API.dll
               ${CMAKE_SOURCE_DIR}/../../build/Debug
               COPYONLY
              )

configure_file(${CMAKE_SOURCE_DIR}/../../lib/Win32/msvcp110.dll
               ${CMAKE_SOURCE_DIR}/../../build/Debug
               COPYONLY
              )


configure_file(${CMAKE_SOURCE_DIR}/../../lib/Win32/msvcr110.dll
               ${CMAKE_SOURCE_DIR}/../../build/Debug
               COPYONLY
              ) 
