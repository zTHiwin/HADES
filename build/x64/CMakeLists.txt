cmake_minimum_required(VERSION 3.26)

set(MyAppName "HADESApp")

project(MyAppName)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ../../lib/x64
                           PUBLIC ../../include
                          )

target_link_directories(${PROJECT_NAME}
                        PRIVATE ../../lib/x64
                        PRIVATE ../../include
                       )

target_link_libraries(${PROJECT_NAME} HIMC_API)

configure_file(${CMAKE_SOURCE_DIR}/../../lib/x64/HIMC_API.dll
               ${CMAKE_SOURCE_DIR}/..
               COPYONLY
              )

configure_file(${CMAKE_SOURCE_DIR}/../../lib/x64/msvcp110.dll
               ${CMAKE_SOURCE_DIR}/../
               COPYONLY
              )


configure_file(${CMAKE_SOURCE_DIR}/../../lib/x64/msvcr110.dll
               ${CMAKE_SOURCE_DIR}/../
               COPYONLY
              ) 
