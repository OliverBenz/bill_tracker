find_package(fmt)
include(ExternalLibs.cmake)

set(libTargetName billTrackerLib)

# Sources
set(libHeaders bill.hpp shop.hpp dateHandler.hpp fileHandling.hpp)
set(libSources dateHandler.cpp fileHandling.cpp)

add_library(${libTargetName} STATIC ${libHeaders} ${libSources})

# Linking
target_link_libraries(${libTargetName} nlohmann_json::nlohmann_json fmt::fmt)
set_target_properties(${libTargetName} PROPERTIES FOLDER "${ideFolderSource}")

# Setup project settings
set_project_warnings(${libTargetName})  # Which warnings to enable
set_compile_options(${libTargetName})   # Which extra compiler flags to enable
set_output_directory(${libTargetName})  # Set the output directory of the library