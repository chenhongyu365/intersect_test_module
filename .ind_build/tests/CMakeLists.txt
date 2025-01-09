cmake_minimum_required(VERSION 3.27)
project(tests CXX C)

# 3rdparty
include("${MODULE_CMAKE_DIR}/3rdparty/googletest.cmake") # googletest
find_gtest()

# tests工具文件
set(TEST_HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/include/utils.hpp"
                      "${CMAKE_CURRENT_LIST_DIR}/include/random.hpp")
source_group("tests_util" FILES ${TEST_HEADER_FILES})
set(TEST_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
source_group("tests_util" FILES ${TEST_SOURCE_FILES})

# 定义测试根目录供使用
add_definitions(-DTEST_ROOT_DIR="${CMAKE_SOURCE_DIR}/tests")

# tests的测试子文件夹
set(TEST_FILES)

if(DEFINED MODULE_TEST_CUSTOM_FILES AND NOT ${MODULE_TEST_CUSTOM_FILES}
                                        STREQUAL "")
    set(TEST_FILES ${MODULE_TEST_CUSTOM_FILES})
else()
    get_all_sources("${CMAKE_SOURCE_DIR}/tests" TEST_FILES)
endif()

set(TEST_SOURCE_FILES ${TEST_SOURCE_FILES} ${TEST_FILES})

# test可执行文件
set(TMP_TARGET_NAME ${PROJECT_NAME})
add_executable(${TMP_TARGET_NAME} ${TEST_HEADER_FILES} ${TEST_SOURCE_FILES})
set_property(TARGET ${TMP_TARGET_NAME} PROPERTY FOLDER "${PROPERTY_PREFIX}")

# 设置目标引用
target_include_directories(${TMP_TARGET_NAME}
                           PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

# 设置目标链接
target_link_libraries(${TMP_TARGET_NAME} PUBLIC ${MODULE_TARGET_NAME})
target_link_libraries(${TMP_TARGET_NAME} PUBLIC gtest gtest_main)
