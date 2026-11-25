list(PREPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/../deps")
if(WIN32)
    list(PREPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/../deps/spdlog")
    find_package(spdlog CONFIG REQUIRED)
else()
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../deps/spdlog/source"
                     "${CMAKE_CURRENT_BINARY_DIR}/spdlog-source" EXCLUDE_FROM_ALL)
endif()
