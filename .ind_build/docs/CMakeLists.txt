cmake_minimum_required(VERSION 3.27)

project(Docs)

# ---- Doxygen variables ----

# set Doxyfile variables
set(DOXYGEN_PROJECT_NAME "Documentation")
set(DOXYGEN_PROJECT_ROOT ${CMAKE_SOURCE_DIR})
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

configure_file(${CMAKE_CURRENT_LIST_DIR}/Doxyfile
               ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_custom_target(
    docs
    ${CMAKE_COMMAND} -E make_directory "${DOXYGEN_OUTPUT_DIRECTORY}"
    COMMAND "doxygen" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    COMMAND echo "Docs written to: ${DOXYGEN_OUTPUT_DIRECTORY}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
set_property(TARGET docs PROPERTY FOLDER "${PROPERTY_PREFIX}")
