cmake_minimum_required(VERSION 2.8)
PROJECT(LockTrace)
set(CMAAKE_CXX_STANDARD 14)

set (SRC "Source")
set(SOURCES
    "${SRC}/main.cpp"
)

source_group(Source FILES ${SOURCES})
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/")