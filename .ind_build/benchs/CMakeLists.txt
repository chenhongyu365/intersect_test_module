cmake_minimum_required(VERSION 3.27)
project(benchs CXX C)

# 3rdparty
include("${MODULE_CMAKE_DIR}/3rdparty/benchmark.cmake") # benchmark
find_benchmark()

# benchmark工具文件
set(BENCH_HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/include/utils.hpp")
source_group("benchmark_utils" FILES ${BENCH_HEADER_FILES})
set(BENCH_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
source_group("benchmark_utils" FILES ${BENCH_SOURCE_FILES})

# 定义测试根目录供使用
add_definitions(-DBENCH_ROOT_DIR="${CMAKE_SOURCE_DIR}/benchs")

# benchmark的测试子文件夹
set(BENCH_FILES)

if(DEFINED MODULE_BENCH_CUSTOM_FILES AND NOT ${MODULE_BENCH_CUSTOM_FILES}
                                         STREQUAL "")
    set(BENCH_FILES ${MODULE_BENCH_CUSTOM_FILES})
else()
    get_all_sources("${CMAKE_SOURCE_DIR}/benchs" BENCH_FILES)
endif()

set(BENCH_SOURCE_FILES ${BENCH_SOURCE_FILES} ${BENCH_FILES})

# benchmark可执行文件
set(TMP_TARGET_NAME ${PROJECT_NAME})
add_executable(${TMP_TARGET_NAME} ${BENCH_HEADER_FILES} ${BENCH_SOURCE_FILES})
set_property(TARGET ${TMP_TARGET_NAME} PROPERTY FOLDER "${PROPERTY_PREFIX}")

# 设置目标引用
target_include_directories(${TMP_TARGET_NAME} PUBLIC ${MODULE_INCLUDE_DIRS})
target_include_directories(${TMP_TARGET_NAME}
                           PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

# 设置目标链接
target_link_libraries(${TMP_TARGET_NAME} PUBLIC ${MODULE_TARGET_NAME})
target_link_libraries(${TMP_TARGET_NAME} PUBLIC benchmark::benchmark
                                                benchmark::benchmark_main)

# 指定benchmark的输出形式
add_definitions(-DBENCHMARK_OUTPUT="console") # console, csv/CSV, json/JSON
