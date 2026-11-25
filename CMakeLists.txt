cmake_minimum_required(VERSION 3.20)
project(VisualInspection VERSION 0.1.0 LANGUAGES CXX)

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Dependencies)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/dist/$<LOWER_CASE:$<CONFIG>>")
add_library(inspection_core STATIC src/inspection.cpp)
target_compile_features(inspection_core PUBLIC cxx_std_17)
target_include_directories(inspection_core PUBLIC include)

add_executable(inspection_demo src/main.cpp)
option(VISUALINSPECTION_INCLUDE_SOURCE "Bundle third-party dependency source archives in dist" OFF)
add_custom_target(inspection_package_files
    COMMAND "${CMAKE_COMMAND}"
            "-DPROJECT_ROOT=${PROJECT_SOURCE_DIR}"
            "-DOUTPUT_DIR=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
            "-DINCLUDE_SOURCE=${VISUALINSPECTION_INCLUDE_SOURCE}"
            -P "${PROJECT_SOURCE_DIR}/cmake/PackageFiles.cmake"
    VERBATIM)
add_dependencies(inspection_demo inspection_package_files)
target_link_libraries(inspection_demo PRIVATE inspection_core spdlog::spdlog)
if(WIN32)
    add_custom_command(TARGET inspection_demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:spdlog::spdlog>" "$<TARGET_FILE_DIR:inspection_demo>"
        VERBATIM)
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(inspection_tests tests/inspection_test.cpp)
    target_link_libraries(inspection_tests PRIVATE inspection_core)
    add_test(NAME threshold_check COMMAND inspection_tests)
endif()
