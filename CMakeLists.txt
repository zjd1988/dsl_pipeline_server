cmake_minimum_required(VERSION 3.10)
project(dsl_pipeline_server)
set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("build for ${CMAKE_BUILD_TYPE}")
# set output verbose build info
set(CMAKE_VERBOSE_MAKEFILEON OFF)

# update compile options
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
endif()

# glib
include(FindPkgConfig)
pkg_check_modules(GLIB REQUIRED glib-2.0)
set(PROJECT_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS})

# cxxopts
set(CXXOPTS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/cxxopts/include)
set(PROJECT_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} ${CXXOPTS_INCLUDE_DIRS})

# spdlog
set(SPDLOG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/spdlog)
set(PROJECT_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} ${SPDLOG_INCLUDE_DIRS})

# ghc filesystem
set(GHC_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/ghc/include)
set(PROJECT_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} ${GHC_INCLUDE_DIRS})

# dsl
set(DSL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deepstream-services-library/src)
set(DSL_LIB_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deepstream-services-library)
set(PROJECT_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} ${DSL_INCLUDE_DIRS})
set(PROJECT_LIB_DIRS ${PROJECT_LIB_DIRS} ${DSL_LIB_DIRS})

# yaml
set(YAML_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/install/include)
set(YAML_LIB_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/install/lib)
set(PROJECT_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} ${YAML_INCLUDE_DIRS})
set(PROJECT_LIB_DIRS ${PROJECT_LIB_DIRS} ${YAML_LIB_DIRS})

# libhv
set(LIBHV_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libhv/install/include/hv)
set(LIBHV_LIB_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libhv/install/lib)
set(PROJECT_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} ${LIBHV_INCLUDE_DIRS})
set(PROJECT_LIB_DIRS ${PROJECT_LIB_DIRS} ${LIBHV_LIB_DIRS})

# get source files
file(GLOB COMMON_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp)
file(GLOB COMPONENT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/component/*.cpp)
file(GLOB PIPELINE_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/pipeline/*.cpp)
file(GLOB SERVER_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/server/*.cpp)

# server app
add_executable(pipeline_server ${COMMON_SRC_FILES}
    ${COMPONENT_SRC_FILES}
    ${PIPELINE_SRC_FILES}
    ${SERVER_SRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server_main.cpp)

target_include_directories(pipeline_server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${PROJECT_INCLUDE_DIRS})
target_link_directories(pipeline_server PRIVATE ${PROJECT_LIB_DIRS})
target_link_libraries(pipeline_server yaml-cpp hv dsl ${GLIB_LIBRARIES})