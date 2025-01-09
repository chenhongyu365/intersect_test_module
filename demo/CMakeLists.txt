cmake_minimum_required(VERSION 3.27)
project(demo CXX C)

set(TMP_TARGET_NAME ${PROJECT_NAME})

get_all_headers(${CMAKE_CURRENT_LIST_DIR} TARGET_HEADER_FILES)
get_all_sources(${CMAKE_CURRENT_LIST_DIR} TARGET_SOURCE_FILES)
set(TARGET_RESOURCE_FILES "ACIS_Win.rc" "ACIS_Win.ico" "small.ico")
add_executable(
    ${TMP_TARGET_NAME} WIN32 ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES}
                             ${TARGET_RESOURCE_FILES})
set_property(TARGET ${TMP_TARGET_NAME} PROPERTY FOLDER "${PROPERTY_PREFIX}")

target_link_libraries(${TMP_TARGET_NAME} PUBLIC ${MODULE_TARGET_NAME})
set(COMMON_LIBS opengl32.lib ${CMAKE_CURRENT_LIST_DIR}/glfw/lib/glfw3_64.lib
                legacy_stdio_definitions.lib)
target_link_libraries(${TMP_TARGET_NAME} PUBLIC ${COMMON_LIBS})

# 设置控制台子系统
if(MSVC)

    if(CMAKE_GENERATOR MATCHES "Ninja")
        add_custom_command(
            TARGET ${TMP_TARGET_NAME}
            POST_BUILD
            COMMAND editbin /SUBSYSTEM:CONSOLE
                    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\\${TMP_TARGET_NAME}.exe")
    else()
        add_custom_command(
            TARGET ${TMP_TARGET_NAME}
            POST_BUILD
            COMMAND editbin /SUBSYSTEM:CONSOLE
                    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TMP_TARGET_NAME}.exe")
    endif()
endif()
