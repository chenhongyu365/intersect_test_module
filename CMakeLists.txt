cmake_minimum_required(VERSION 3.27)

include(config.cmake)

# ---------------------------------------------------------------------------------------
# Config Preprocess
# ---------------------------------------------------------------------------------------
string(TOLOWER ${MODULE_NAME} MODULE_NAME_LOWER)
string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)
set(MODULE_VERSION
    "${MODULE_VERSION_MAJOR}.${MODULE_VERSION_MINOR}.${MODULE_VERSION_PATCH}")

# build option
option(MODULE_IND_BUILD "build as module(OFF) or as independent project(ON)" ON
)# module独立编译选项

if(${PROJ_SUPER_BUILD}) # ${PROJ_SUPER_BUILD} 若未定义则为FALSE
    set(MODULE_IND_BUILD OFF) # 如果该项目作为模块通过上层构建，则强制更改为“作为模块build”
endif()

set(MODULE_SUPER_BUILD ${MODULE_IND_BUILD}) # independent build IS super-build

# ---------------------------------------------------------------------------------------
# Start project
# ---------------------------------------------------------------------------------------
project(
    ${MODULE_NAME_LOWER}
    VERSION ${MODULE_VERSION}
    DESCRIPTION ""
    HOMEPAGE_URL ""
    LANGUAGES CXX C)
message(STATUS "Build ${PROJECT_NAME}: ${PROJECT_VERSION}")
set(MODULE_TARGET_NAME ${PROJECT_NAME})

# ---------------------------------------------------------------------------------------
# Create module header folder and Generate version.h
# ---------------------------------------------------------------------------------------
file(MAKE_DIRECTORY "${MODULE_INCLUDE_DIR}/${MODULE_NAME_LOWER}")
configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/version.h.in"
    "${MODULE_INCLUDE_DIR}/${MODULE_NAME_LOWER}_version.h" @ONLY
)# 根据.h.in生成.h文件

# ---------------------------------------------------------------------------------------
# Options and vars
# ---------------------------------------------------------------------------------------
set(PROPERTY_PREFIX "${PROJECT_NAME}")

# ---------------------------------------------------------------------------------------
# Set build and c++ options
# ---------------------------------------------------------------------------------------
# 若内置变量CMAKE_BUILD_TYPE未被设置，则强制将其设为字符串"Release"，并存在Cache中
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE
        "Release"
        CACHE STRING "Choose Release or Debug" FORCE)
endif()

if(NOT CMAKE_CONFIGURATION_TYPES)
    # Debug;Release;RelWithDebInfo;MinSizeRel
    set(CMAKE_CONFIGURATION_TYPES
        "Debug;Release"
        CACHE STRING "Release and Debug" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # force C++20
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_DEBUG_POSTFIX d) # 使用 Debug 配置构建时会为文件添加后缀 d

# make sure __cplusplus is defined when using msvc and enable parallel build
if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus /MP")
    # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")  # /MT
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL") # /MD
    # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")  # /MTd
    # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")  # /MDd
endif()

# 编译器选项
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # todo
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wno-error)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # todo
endif()

# ---------------------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------------------
set(MODULE_INDBUILD_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/.ind_build") # 独立构建前缀路径

# # 预定义宏
add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DCUSTOM_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DCUSTOM_LOG_DIR="${CMAKE_CURRENT_SOURCE_DIR}/log")
add_definitions(-DCUSTOM_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")
add_definitions(-DCUSTOM_CONFIG_DIR="${CMAKE_CURRENT_SOURCE_DIR}/config")

# # 框架路径
set(MODULE_CMAKE_DIR ${MODULE_INDBUILD_PREFIX}/cmake)
set(MODULE_DEPS_DIR ${MODULE_INDBUILD_PREFIX}/3rdparty)
set(MODULE_SAMPLES_DIR ${MODULE_INDBUILD_PREFIX}/samples)
set(MODULE_SCRIPTS_DIR ${MODULE_INDBUILD_PREFIX}/scripts)
set(MODULE_DOCS_DIR ${MODULE_INDBUILD_PREFIX}/docs)
set(MODULE_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(MODULE_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out)
set(MODULE_BUILD_DEPS_DIR ${MODULE_BUILD_DIR}/_deps) # FetchContent_Declare的工作路径
set(MODULE_COMMON_INCLUDE_DIRS ${MODULE_DEPS_DIR}
                               "${MODULE_INCLUDE_DIR}/${MODULE_NAME_LOWER}")

# 根据构建配置来设置输出directory 这里用到CMake生成器表达式
set(MODULE_OUT_DIR_DIFF_BUILD_TYPE
    "$<$<CONFIG:Debug>:"
    "${MODULE_OUT_DIR}/Debug"
    ">"
    "$<$<CONFIG:Release>:"
    "${MODULE_OUT_DIR}/Release"
    ">"
    "$<$<CONFIG:RelWithDebInfo>:"
    "${MODULE_OUT_DIR}/RelWithDebInfo"
    ">"
    "$<$<CONFIG:MinSizeRel>:"
    "${MODULE_OUT_DIR}/MinSizeRel"
    ">")

# 生成器表达式生成的字符串包含分号作为分隔符，删除得到路径字符串。
string(REPLACE ";" "" MODULE_OUT_DIR_DIFF_BUILD_TYPE
               ${MODULE_OUT_DIR_DIFF_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MODULE_OUT_DIR_DIFF_BUILD_TYPE}
)# 可执行Target文件的输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MODULE_OUT_DIR_DIFF_BUILD_TYPE}
)# 共享库Target文件的输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MODULE_OUT_DIR_DIFF_BUILD_TYPE}
)# 静态库Target文件的输出路径
set(MODULE_DLL_OUTPUT_DIR ${MODULE_OUT_DIR_DIFF_BUILD_TYPE}) # DLL文件移动目标路径

# # 框架项目选项
option(MODULE_BUILD_TESTS "Whether to build the module: test" ON)
option(MODULE_BUILD_BENCHS "Whether to build the module: benchmark" OFF)
option(MODULE_BUILD_FORMAT "Whether to build the format tool" ON)
option(MODULE_BUILD_INSTALL "Generate the install target" OFF)
option(MODULE_BUILD_SAMPLES "Whether to build the sample" OFF) # sample
option(MODULE_BUILD_DEMO "Whether to build the demo" OFF) # demo

# option
option(MODULE_BUILD_DOXYGEN "Whether to build the module: DocGenerate" ON
)# doxygen编译开关

# ---------------------------------------------------------------------------------------
# 3rdparty
# ---------------------------------------------------------------------------------------
include("${MODULE_CMAKE_DIR}/3rdparty/acis.cmake")
set(MODULE_ACIS_VERSION
    "R34"
    CACHE STRING "ACIS version linked")
find_acis(${MODULE_ACIS_VERSION})

# ---------------------------------------------------------------------------------------
# Library
# ---------------------------------------------------------------------------------------
include("${MODULE_CMAKE_DIR}/frame_utils.cmake")
get_all_headers(${MODULE_INCLUDE_DIR} TARGET_HEADER_FILES)
source_group(
    TREE "${CMAKE_CURRENT_LIST_DIR}/include/${MODULE_NAME_LOWER}"
    PREFIX "include"
    FILES ${TARGET_HEADER_FILES})
set(TARGET_HEADER_FILES ${TARGET_HEADER_FILES} ${MODULE_HEADERS})
get_all_sources(${MODULE_SOURCE_DIR} TARGET_SOURCE_FILES)
source_group(
    TREE "${CMAKE_CURRENT_LIST_DIR}/src"
    PREFIX "src"
    FILES ${TARGET_SOURCE_FILES})

if("${TARGET_SOURCE_FILES}" STREQUAL "")
    message(WARNING "This folder has no sources!!!")
else()
    # 在当前目录下创建了一个名为 MODULE_TARGET_NAME 的动态库目标，使用之前获取的头文件与源文件
    add_library(${MODULE_TARGET_NAME} SHARED ${TARGET_HEADER_FILES}
                                             ${TARGET_SOURCE_FILES}) # 添加链接库输出

    # 为刚创建的动态库设置FOLDER属性，这个动态库被放置在项目中以 PROPERTY_PREFIX 命名的文件夹下
    set_property(TARGET ${MODULE_TARGET_NAME} PROPERTY FOLDER
                                                       ${PROPERTY_PREFIX})

    # ACIS target_include_acis(${MODULE_TARGET_NAME})
    target_include_directories(
        ${MODULE_TARGET_NAME}
        PUBLIC "$<BUILD_INTERFACE:${ACIS_UTILS_HEADER_DIR}>"
               "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
    target_link_acis(${MODULE_TARGET_NAME} ${MODULE_DLL_OUTPUT_DIR})

    # 设置目标引用
    target_include_directories(
        ${MODULE_TARGET_NAME}
        PUBLIC "$<BUILD_INTERFACE:${MODULE_COMMON_INCLUDE_DIRS}>"
               "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

    # 在这里可以发现 target_include_directories 中的 ${MODULE_COMMON_INCLUDE_DIRS} 包含
    # add_library 时的 ${MODULE_INCLUDE_DIR} 因为 add_library
    # 命令只是定义了目标，target_include_directories设置目标的头文件包含目录。
    # 这样使用MODULE_COMMON_INCLUDE_DIRS集中管理头文件，便于维护迁移。
endif()

# ---------------------------------------------------------------------------------------
# Binary
# ---------------------------------------------------------------------------------------
# add_subdirectory 后，会执行对应子目录中的CMakeList文件
if(${MODULE_BUILD_SAMPLES})
    add_subdirectory("${MODULE_INDBUILD_PREFIX}/samples")
endif()

if(${MODULE_BUILD_TESTS})
    add_subdirectory("${MODULE_INDBUILD_PREFIX}/tests")
endif()

if(${MODULE_BUILD_BENCHS})
    add_subdirectory("${MODULE_INDBUILD_PREFIX}/benchs")
endif()

if(${MODULE_BUILD_DEMO})
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/demo")
endif()

# ---------------------------------------------------------------------------------------
# Chore
# ---------------------------------------------------------------------------------------
if(${MODULE_BUILD_DOXYGEN})
    add_subdirectory("${MODULE_INDBUILD_PREFIX}/docs")
endif()

# cmake-format
if(${MODULE_BUILD_FORMAT})
    find_package(Python REQUIRED)

    # 定义了名为 format 的自定义目标，并在${CMAKE_CURRENT_SOURCE_DIR}目录下运行format.py
    add_custom_target(
        format
        COMMAND ${Python_EXECUTABLE} ${MODULE_SCRIPTS_DIR}/format.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    set_property(TARGET format PROPERTY FOLDER "${PROPERTY_PREFIX}"
    )# 放置在项目中以 PROPERTY_PREFIX 命名的文件夹下

    add_custom_target(
        format-check
        COMMAND ${Python_EXECUTABLE} ${MODULE_SCRIPTS_DIR}/format_check.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    set_property(TARGET format-check PROPERTY FOLDER "${PROPERTY_PREFIX}")
endif()

# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------
# ATTENTION: ind-build should not support Install
