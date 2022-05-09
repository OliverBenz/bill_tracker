# ----- External Libraries -----
find_package(Qt6 REQUIRED COMPONENTS Gui Widgets)
include(ExternalLibs.cmake)

set(CMAKE_AUTOMOC ON) # Qt6 Settings
set(CMAKE_AUTORCC ON) # Qt6 Settings
set(CMAKE_AUTOUIC ON) # Qt6 Settings


# Settings
set(targetName "billTracker")

# Get files to build
set(headers
    inputWindow.hpp
    lib/bill.hpp
    lib/fileHandling.hpp
)
set(sources
    main.cpp
    inputWindow.cpp
    lib/bill.cpp
    lib/fileHandling.cpp
)

# Create library
add_executable(${targetName}
    # Common modules
    ${headers}
    ${sources}
)


# Link to thread module for maths functions.
target_link_libraries(${targetName} PRIVATE Qt6::Gui Qt6::Widgets nlohmann_json::nlohmann_json)
set_target_properties(${targetName} PROPERTIES FOLDER "${ideFolderSource}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable
set_output_directory(${targetName})  # Set the output directory of the library

# Copy header files to output after build
# copy_headers_to_output(${targetName} "${headers}")

# Specify version
target_compile_definitions(${targetName} PUBLIC VERSION_MAJOR=0)
target_compile_definitions(${targetName} PUBLIC VERSION_MINOR=0)
target_compile_definitions(${targetName} PUBLIC VERSION_PATCH=1)

# System installation
# install(TARGETS ${targetName} DESTINATION lib)
# install(FILES ${headers} DESTINATION include/!!Target!!)