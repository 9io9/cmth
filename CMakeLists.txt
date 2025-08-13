cmake_minimum_required(VERSION 3.25.1)

project(cmth VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/ec.h 
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/tools/pec/pec.py ${CMAKE_CURRENT_SOURCE_DIR}/.ec ${CMAKE_CURRENT_SOURCE_DIR}/include/ec.h _LJW_CMTH_EC_H_
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/.ec ${CMAKE_CURRENT_SOURCE_DIR}/tools/pec/pec.py
    COMMENT "convert .ec to error code header file"
)

add_custom_target(cmthgech DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/ec.h)

add_library(cmth STATIC src/calc.c)
add_dependencies(cmth cmthgech)

target_include_directories(cmth PRIVATE include)

set_target_properties(cmth PROPERTIES EXPORT_NAME cmth)

install(
    TARGETS cmth
    EXPORT cmthTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include DESTINATION include)
install(
    EXPORT cmthTargets
    FILE cmthTargets.cmake
    NAMESPACE cmth::
    DESTINATION lib/cmake/cmth
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    cmthConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_file(cmthConfig.cmake.in cmthConfig.cmake @ONLY)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/cmthConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/cmthConfigVersion.cmake"
    DESTINATION lib/cmake/cmth
)
install(
    EXPORT cmthTargets
    FILE cmthTargets.cmake
    NAMESPACE cmth::
    DESTINATION lib/cmake/cmth
)

enable_testing()
add_subdirectory(test)