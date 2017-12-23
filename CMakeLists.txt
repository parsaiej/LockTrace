cmake_minimum_required(VERSION 2.8)
PROJECT(LockTrace)
set(CMAAKE_CXX_STANDARD 14)

set (SRC "Source")

set(SOURCES
    "${SRC}/main.cpp"	
)

set(HEADERS
	"${SRC}/Vec3.h"
	"${SRC}/Ray.h"
	"${SRC}/Hitable.h"
	"${SRC}/HitableList.h"
	"${SRC}/Sphere.h"
	"${SRC}/Material.h"
)

source_group(Source FILES ${SOURCES})
source_group(Header FILES $(HEADERS))
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/")