set(spdlog_source "${PROJECT_ROOT}/deps/spdlog/source")
set(licenses "${OUTPUT_DIR}/licenses")
configure_file("${PROJECT_ROOT}/LICENSE" "${licenses}/VisualInspection-LICENSE.txt" COPYONLY)
configure_file("${spdlog_source}/LICENSE" "${licenses}/spdlog-LICENSE.txt" COPYONLY)
configure_file("${spdlog_source}/include/spdlog/fmt/bundled/fmt.license.rst"
               "${licenses}/fmt-LICENSE.rst" COPYONLY)

# Recreate this generated directory so removed sources never survive a rebuild.
set(bundle "${OUTPUT_DIR}/third_party")
file(REMOVE_RECURSE "${bundle}")
if(INCLUDE_SOURCE)
    file(MAKE_DIRECTORY "${bundle}/spdlog")
    file(GLOB entries RELATIVE "${spdlog_source}" "${spdlog_source}/*")
    list(REMOVE_ITEM entries ".git" "build")
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E tar cf "${bundle}/spdlog/spdlog-source.zip"
                --format=zip -- ${entries}
        WORKING_DIRECTORY "${spdlog_source}"
        COMMAND_ERROR_IS_FATAL ANY)
endif()
