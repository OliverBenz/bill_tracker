if(NOT BUILD_TESTS)
    return()
endif()

# Settings
include(FetchGTest.cmake)
set(targetName "!!Template!!.gtest")

# Get files to build
set(sources )
set(headers )

include_directories("../src/")

# Create executable
add_executable(${targetName}
    ${sources}
    ${headers}
)

# Link to required libraries
target_link_libraries(${targetName} PUBLIC !!Template!! gtest_main)
set_target_properties(${targetName} PROPERTIES FOLDER "${ideFolderSource}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable

# Add tests
add_test(NAME ${targetName} COMMAND tests)